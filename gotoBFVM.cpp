#include <cstdio>
#include <cstring>

#define MAX_DATA 100000
#define MAX_CODE 10240
#define MAX_TMP_CODE 4096
#define MAX_INPUT 4096
#define uint unsigned int

uint data[MAX_DATA];
uint code[MAX_CODE];
uint oldPos[MAX_CODE];
char input[MAX_INPUT];

inline uint optimizeCode(char* const tmpCode, const uint codeSize, const uint memorySize) {
  uint ic[MAX_CODE];
  uint jmpStackHead = 0;
  uint jmpStack[MAX_CODE];

  uint newCodeSize = 0;
  uint icHead = 0;
  
  #define compress(ch, alias)          \
    code[newCodeSize++] = alias;       \
    code[newCodeSize] = 1;             \
    while(1) {                         \
      if(tmpCode[c + 1] == ch) {       \
        ++code[newCodeSize];           \
        ++c;                           \
      }                                \
      else if(tmpCode[c + 1] == '.') { \
        ++c;                           \
        continue;                      \
      }                                \
      else {                           \
        break;                         \
      }                                \
    }                                  \
    ic[icHead] += code[newCodeSize++]; \
    
  uint c = 0;
  while(c < codeSize) {
    uint max = codeSize;
    
    for(uint cc = c; cc < codeSize; ++cc) {
      char ch = tmpCode[cc];
      if(ch == '[' || ch == ']' || ch == '<' || ch == '>') {
        max = cc + 1;
        break;
      }
      else if(ch == ',') {
        c = cc;
        break;
      }
    }
    
    for(; c < max; ++c) {
      switch(tmpCode[c]) {
        case '+': compress('+', 0); break;
        case '-': compress('-', 1); code[newCodeSize - 1] %= 256; break;
        case '>': compress('>', 2); break;
        case '<': compress('<', 3); code[newCodeSize - 1] %= memorySize; break;
        case ',': code[newCodeSize++] = 4; ++ic[icHead]; break;
        case '[':
          code[newCodeSize++] = 5;
          oldPos[newCodeSize] = c;
          jmpStack[++jmpStackHead] = ++newCodeSize;
          ic[++icHead] = 1;
          break;
        case ']':
          code[newCodeSize] = 6;
          code[newCodeSize + 1] = jmpStack[jmpStackHead];
          code[newCodeSize + 3] = ic[icHead--];
          oldPos[newCodeSize + 3] = c;
          newCodeSize += 4;
          code[jmpStack[jmpStackHead--] - 1] = newCodeSize;
          break;
      }
    }
  }
  #undef compress
  return newCodeSize;
}

int main() {
  uint cases;
  scanf("%u", &cases);
  
  const void *const jmpTable[] = { &&add, &&sub, &&rdata, &&ldata, &&in, &&lbracket, &&rbracket };
  
  for(uint i = 0; i < cases; ++i) {
    uint cptr = 0;
    uint dptr = 0;
    uint iptr = 0;
    uint memorySize;
    uint tmpCodeSize;
    uint inputSize;
    
    scanf("%u %u %u\n", &memorySize, &tmpCodeSize, &inputSize);
    if(i != 0) {
      memset(data, 0, sizeof(uint) * memorySize);
    }
    
    fgets(input, tmpCodeSize + 1, stdin);
    uint codeSize = optimizeCode(input, tmpCodeSize, memorySize);
    
    fgets(input, 2, stdin); // Read to the next line
    fgets(input, inputSize + 1, stdin);
    
    goto nop;
    add:
      printf("hurr\n");
      data[dptr] = (data[dptr] + code[cptr++]) % 256;
      goto nop;
    sub:
      data[dptr] = (256 + data[dptr] - code[cptr++]) % 256;
      goto nop;
    rdata:
      dptr = (dptr + code[cptr++]) % memorySize;
      goto nop;
    ldata:
      dptr = (memorySize + dptr - code[cptr++]) % memorySize;
      goto nop;
    in:
      data[dptr] = iptr != inputSize ? input[iptr++] : 255;
      goto nop;
    lbracket:
      if(data[dptr] == 0) {
        cptr = code[cptr];
      } else {
        code[code[cptr] - 2] = 0;
        ++cptr;
      }
      goto nop;
    rbracket:
      cptr += 3;
      if(data[dptr] != 0) {
        code[cptr - 2] += code[cptr - 1];
        
        if(code[cptr - 2] < 50000000) {
          cptr = code[cptr - 3];
        } else {
          printf("Loops %u %u\n", oldPos[code[cptr - 3] - 1], oldPos[cptr - 1]);
          goto kill;
        }
      }
    nop:
    while(cptr < codeSize) {
      goto *jmpTable[code[cptr++]];
    }
    
    fwrite("Terminates\n", sizeof(char), 11, stdout);
    kill:
    continue;
  }
  return 0;
}
