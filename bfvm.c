#include <string.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdint.h>

#define MAX_DATA 100000
#define MAX_INPUT 4096
#define uint uint32_t
#define byte uint8_t

typedef struct {
  uint jmpTo;
  uint instructions;
  uint index;
} link;

uint data[MAX_DATA];
char input[MAX_INPUT];
link linker[MAX_INPUT];

void compileBF(byte* const code, const char* const bfCode, const uint bfCodeSize) {
  // rdi is the pointer to memory
  // rsi is the size of memory
  // rdx is the pointer to input
  // rcx is the size of input
  // r8 is the data index
  // r9 is the input index
  // r10 is general use. no one likes r10
  // rax is general use too but everyone likes rax
  // r11 is for keeping count of the bf instructions done in the current loop
  // r12 is non-volatile and is used to restore the rsp after we destroy it
  
  /*
  xor r8, r8
  xor r9, r9
  xor r11, r11
  push r12
  mov r12, rsp
  */
  const byte init_code[] = { 0x4D, 0x31, 0xC0, 0x4D, 0x31, 0xC9, 0x4D, 0x31, 0xDB, 0x41, 0x54, 0x49, 0x89, 0xE4 };
  const uint init_code_size = sizeof(init_code) / sizeof(byte);
  
  /*
  mov rsp, r12
  pop r12
  xor eax, eax
  mov [rdi], eax
  mov [rdi+4], eax
  ret
  */
  const byte exit_code[] = { 0x4C, 0x89, 0xE4, 0x41, 0x5C, 0x48, 0x31, 0xC0, 0x89, 0x07, 0x89, 0x47, 0x04, 0xC3 };
  const uint exit_code_size = sizeof(exit_code) / sizeof(byte);
  
  /*
  lea r10, [rdi+r8*4]
  mov eax, DWORD PTR [r10]
  add eax, 0xFFAACCEE
  and eax, 0xff
  mov DWORD PTR [r10], eax
  */
  const byte add_code[] = { 0x4E, 0x8D, 0x14, 0x87, 0x41, 0x8B, 0x02, 0x05, 0xEE, 0xCC, 0xAA, 0xFF, 0x25, 0xFF, 0x00, 0x00, 0x00, 0x41, 0x89, 0x02 };
  const uint add_code_size = sizeof(add_code) / sizeof(byte);
  
  /*
  mov r10, rdx
  mov rax, r8
  add rax, 99999999
  xor rdx, rdx
  div rsi
  mov r8, rdx
  mov rdx, r10
  */
  const byte rdata_code[] = { 0x49, 0x89, 0xD2, 0x4C, 0x89, 0xC0, 0x48, 0x05, 0xFF, 0xE0, 0xF5, 0x05, 0x48, 0x31, 0xD2, 0x48, 0xF7, 0xF6, 0x49, 0x89, 0xD0, 0x4C, 0x89, 0xD2 };
  const uint rdata_code_size = sizeof(rdata_code) / sizeof(byte);
  
  /*
  mov r10, rdx
  mov rax, rsi
  add rax, r8
  add rax, 99999999
  xor rdx, rdx
  div rsi
  mov r8, rdx
  mov rdx, r10
  */
  const byte ldata_code[] = { 0x49, 0x89, 0xD2, 0x48, 0x89, 0xF0, 0x4C, 0x01, 0xC0, 0x48, 0x05, 0xFF, 0xE0, 0xF5, 0x05, 0x48, 0x31, 0xD2, 0x48, 0xF7, 0xF6, 0x49, 0x89, 0xD0, 0x4C, 0x89, 0xD2 };
  const uint ldata_code_size = sizeof(ldata_code) / sizeof(byte);
  
  /*
  cmp rcx, r9
  je use_255
  mov eax, [rdx+r9*4]
  mov [rdi+r8*4], eax
  add r9, 1
  jmp done
use_255:
  mov eax, 255
  mov [rdi+r8*4], eax
done:
  */
  const byte input_code[] = { 0x4C, 0x39, 0xC9, 0x74, 0x0E, 0x42, 0x8B, 0x04, 0x8A, 0x42, 0x89, 0x04, 0x87, 0x49, 0x83, 0xC1, 0x01, 0xEB, 0x09, 0xB8, 0xFF, 0x00, 0x00, 0x00, 0x42, 0x89, 0x04, 0x87 };
  const uint input_code_size = sizeof(input_code) / sizeof(byte);
  
  /*
  mov eax, [rdi+r8*4]
  cmp eax, 0
  je 0
  push r11
  xor r11, r11
  */
  const byte start_loop_code[] = { 0x42, 0x8B, 0x04, 0x87, 0x83, 0xF8, 0x00, 0x0F, 0x84, 0x00, 0x00, 0x00, 0x00, 0x41, 0x53, 0x4D, 0x31, 0xDB };
  const uint start_loop_code_size = sizeof(start_loop_code) / sizeof(byte);
  
  /*
  mov eax, [rdi+r8*4]
  cmp eax, 0
  jne goback
  jmp done
goback:
  add r11, 999999
  cmp r11, 50000000
  jl 0
  mov eax, 999999
  mov r10d, 999999
  mov [rdi], eax
  mov [rdi+4], r10d
  mov rsp, r12
  pop r12
  ret
done:
  pop r11
  */
  const byte stop_loop_code[] = { 0x42, 0x8B, 0x04, 0x87, 0x83, 0xF8, 0x00, 0x75, 0x02, 0xEB, 0x2B, 0x49, 0x81, 0xC3, 0x3F, 0x42, 0x0F, 0x00, 0x49, 0x81, 0xFB, 0x80, 0xF0, 0xFA, 0x02, 0x0F, 0x8C, 0x00, 0x00, 0x00, 0x00, 0xB8, 0x3F, 0x42, 0x0F, 0x00, 0x41, 0xBA, 0x3F, 0x42, 0x0F, 0x00, 0x89, 0x07, 0x44, 0x89, 0x57, 0x04, 0x4C, 0x89, 0xE4, 0x41, 0x5C, 0xC3, 0x41, 0x5B };
  const uint stop_loop_code_size = sizeof(stop_loop_code) / sizeof(byte);
  
  uint cs = 0; // code size
  uint linkerStack = 0;
  int jmpTo = 0;
  int amt = 0;
  memcpy(&code[0], init_code, init_code_size);
  cs += init_code_size;
  
  for(uint i = 0; i < bfCodeSize; ++i) {
    link* l = &linker[linkerStack];
    switch(bfCode[i]) {
      case '+':
      case '-':
        amt = 0;
        while(i < bfCodeSize) {
          if(bfCode[i] == '+') {
            ++amt;
          } else if(bfCode[i] == '-') {
            --amt;
          } else if(bfCode[i] == ',') {
            amt = 0; // no point in doing anything
            break;   // if input is just going to override it
          } else if(bfCode[i] != '.') {
            --i;
            break;
          }
          ++l->instructions;
          ++i;
        }
        
        if(amt != 0) {
          memcpy(&code[cs], add_code, add_code_size);
          code[cs + 8] = amt & 0x000000FF;
          code[cs + 9] = (amt & 0x0000FF00) >> 8;
          code[cs + 10] = (amt & 0x00FF0000) >> 16;
          code[cs + 11] = (amt & 0xFF000000) >> 24;
          cs += add_code_size;
        }
        break;
      case '>':
      case '<':
        amt = 0;
        while(i < bfCodeSize) {
          if(bfCode[i] == '>') {
            ++amt;
          } else if(bfCode[i] == '<') {
            --amt;
          } else if(bfCode[i] != '.') {
            --i;
            break;
          }
          ++i;
          ++l->instructions;
        }
        
        if(amt < 0) {
          memcpy(&code[cs], ldata_code, ldata_code_size);
          code[cs + 11] = amt & 0x000000FF;
          code[cs + 12] = (amt & 0x0000FF00) >> 8;
          code[cs + 13] = (amt & 0x00FF0000) >> 16;
          code[cs + 14] = (amt & 0xFF000000) >> 24;
          cs += ldata_code_size;
        } else if(amt > 0) {
          memcpy(&code[cs], rdata_code, rdata_code_size);
          code[cs + 8] = amt & 0x000000FF;
          code[cs + 9] = (amt & 0x0000FF00) >> 8;
          code[cs + 10] = (amt & 0x00FF0000) >> 16;
          code[cs + 11] = (amt & 0xFF000000) >> 24;
          cs += rdata_code_size;
        }
        break;
      case ',':
        ++l->instructions;
        memcpy(&code[cs], input_code, input_code_size);
        cs += input_code_size;
        break;
      case '[':
        memcpy(&code[cs], start_loop_code, start_loop_code_size);
        l = &linker[++linkerStack];
        l->jmpTo = cs;
        l->instructions = 1;
        l->index = i;
        cs += start_loop_code_size;
        break;
      case ']':
        memcpy(&code[cs], stop_loop_code, stop_loop_code_size);
        
        jmpTo = l->jmpTo - cs - 13;
        code[cs + 27] = jmpTo & 0x000000FF;
        code[cs + 28] = (jmpTo & 0x0000FF00) >> 8;
        code[cs + 29] = (jmpTo & 0x00FF0000) >> 16;
        code[cs + 30] = (jmpTo & 0xFF000000) >> 24;
        
        jmpTo = cs + stop_loop_code_size - l->jmpTo - 13;
        code[l->jmpTo + 9] = jmpTo & 0x000000FF;
        code[l->jmpTo + 10] = (jmpTo & 0x0000FF00) >> 8;
        code[l->jmpTo + 11] = (jmpTo & 0x00FF0000) >> 16;
        code[l->jmpTo + 12] = (jmpTo & 0xFF000000) >> 24;
        
        code[cs + 14] = l->instructions & 0x000000FF;
        code[cs + 15] = (l->instructions & 0x0000FF00) >> 8;
        code[cs + 16] = (l->instructions & 0x00FF0000) >> 16;
        code[cs + 17] = (l->instructions & 0xFF000000) >> 24;
        
        code[cs + 32] = l->index & 0x000000FF;
        code[cs + 33] = (l->index & 0x0000FF00) >> 8;
        code[cs + 34] = (l->index & 0x00FF0000) >> 16;
        code[cs + 35] = (l->index & 0xFF000000) >> 24;
        
        code[cs + 38] = i & 0x000000FF;
        code[cs + 39] = (i & 0x0000FF00) >> 8;
        code[cs + 40] = (i & 0x00FF0000) >> 16;
        code[cs + 41] = (i & 0xFF000000) >> 24;
        
        --linkerStack;
        cs += stop_loop_code_size;
        break;
      case '.':
        ++l->instructions;
        break;
    }
  }
  
  memcpy(&code[cs], exit_code, exit_code_size);
}

int main() {
  // careful with the allocation size
  void* codeMem = mmap(NULL, 4096 * 10, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
  
  // don't look directly at it
  volatile int (*func) (uint*, uint, char*, uint) = 
  (volatile int (*) (uint*, uint, char*, uint))codeMem;
  
  uint cases;
  scanf("%u", &cases);
  
  for(uint i = 0; i < cases; ++i) {
    uint memorySize;
    uint bfCodeSize;
    uint inputSize;
    
    scanf("%u %u %u\n", &memorySize, &bfCodeSize, &inputSize);
    if(i != 0) {
      memset(data, 0, sizeof(uint) * memorySize);
    }
    
    fgets(input, bfCodeSize + 1, stdin);
    compileBF((byte* )codeMem, input, bfCodeSize);
    
    fgets(input, 2, stdin); // read to the next line
    fgets(input, inputSize + 1, stdin);
    
    func(data, memorySize, input, inputSize);
    
    if(data[0] == 0 && data[1] == 0) {
      printf("Terminates\n");
    } else {
      printf("Loops %d %d\n", data[0], data[1]);
    }
  }
  return 0;
}
