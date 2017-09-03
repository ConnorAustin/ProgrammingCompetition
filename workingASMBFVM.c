#include <string.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdint.h>
#define uint unsigned int

#define MAX_DATA 100000
#define MAX_INPUT 4096
#define uint unsigned int
#define byte uint8_t

typedef struct {
  uint jmpTo;
  uint instructions;
} link;

uint data[MAX_DATA];
char input[MAX_INPUT];
link linker[MAX_INPUT];

void hexDump(byte* code, uint size) {
  for(uint i = 0; i < size; ++i) {
    printf("%0x: %0x\n", i, code[i]);
  }
  printf("\n");
}

uint compileBF(byte* const code, const char* const bfCode, const uint bfCodeSize) {
  // rdi is the pointer to memory
  // rsi is the size of memory
  // rdx is the pointer to input
  // rcx is the size of input
  // r8 is the data index
  // r9 is the input index
  // r10 is general use. no one likes r10
  // rax is general use too. but everyone likes rax
  // r11 is for keeping count of the bf instructions done in the current loop
  // r12 is non-volatile and is used to restore the rsp after we destroy it
  
  /*
  xor r8, r8
  xor r9, r9
  push r12
  mov r12, rsp
  */
  const byte init_code[] = { 0x4D, 0x31, 0xC0, 0x4D, 0x31, 0xC9, 0x41, 0x54, 0x49, 0x89, 0xE4 };
  const uint init_code_size = sizeof(init_code) / sizeof(byte);
  
  /*
  mov rsp, r12
  pop r12
  ret
  */
  const byte exit_code[] = { 0x4C, 0x89, 0xE4, 0x41, 0x5C, 0xC3 };
  const uint exit_code_size = sizeof(exit_code) / sizeof(byte);
  
  /*
  lea    r10,[rdi+r8*4]
  mov    eax,DWORD PTR [r10]
  add    eax,0x1
  and    eax,0xff
  mov    DWORD PTR [r10],eax
  */
  const byte add_code[] = { 0x4E, 0x8D, 0x14, 0x87, 0x41, 0x8B, 0x02, 0x83, 0xC0, 0x01, 0x25, 0xFF, 0x00, 0x00, 0x00, 0x41, 0x89, 0x02 };
  const uint add_code_size = sizeof(add_code) / sizeof(byte);
  
  /*
  lea    r10,[rdi+r8*4]
  mov    eax,DWORD PTR [r10]
  add    eax,0xff
  and    eax,0xff
  mov    DWORD PTR [r10],eax
  */
  const byte sub_code[] = { 0x4E, 0x8D, 0x14, 0x87, 0x41, 0x8B, 0x02, 0x05, 0xFF, 0x00, 0x00, 0x00, 0x25, 0xFF, 0x00, 0x00, 0x00, 0x41, 0x89, 0x02 };
  const uint sub_code_size = sizeof(sub_code) / sizeof(byte);
  
  /*
  mov    rax,r8
  add    rax,0x1
  xor    rdx,rdx
  div    rsi
  mov    r8,rdx
  */
  const byte rdata_code[] = { 0x4c, 0x89, 0xc0, 0x48, 0x83, 0xc0, 0x01, 0x48, 0x31, 0xd2, 0x48, 0xf7, 0xf6, 0x49, 0x89, 0xd0 };
  const uint rdata_code_size = sizeof(rdata_code) / sizeof(byte);

  /*
  mov    rax,rsi
  add    rax,r8
  sub    rax,0x1
  xor    rdx,rdx
  div    rsi
  mov    r8,rdx
  */
  const byte ldata_code[] = { 0x48, 0x89, 0xf0, 0x4c, 0x01, 0xc0, 0x48, 0x83, 0xe8, 0x01, 0x48, 0x31, 0xd2, 0x48, 0xf7, 0xf6, 0x49, 0x89, 0xd0 };
  const uint ldata_code_size = sizeof(ldata_code) / sizeof(byte);
  
  /*
  cmp rcx, r9
  je use_zero
  lea r10, [rdx+r9]
  mov rax, [r10]
  and rax, 0xFF
  lea r10, [rdi+r8*4]
  mov [r10], rax
  add r9, 1
  jmp done
use_zero:
  lea r10, [rdi+r8*4]
  xor rax, rax
  mov [r10], rax
done:
  */
  const byte input_code[] = { 0x4C, 0x39, 0xC9, 0x74, 0x1A, 0x4E, 0x8D, 0x14, 0x0A, 0x49, 0x8B, 0x02, 0x48, 0x25, 0xFF, 0x00, 0x00, 0x00, 0x4E, 0x8D, 0x14, 0x87, 0x49, 0x89, 0x02, 0x49, 0x83, 0xC1, 0x01, 0xEB, 0x0A, 0x4E, 0x8D, 0x14, 0x87, 0x48, 0x31, 0xC0, 0x49, 0x89, 0x02 };
  const uint input_code_size = sizeof(input_code) / sizeof(byte);
  
  /*
  lea r10, [rdi+r8*4]
  mov rax, [r10]
  cmp rax, 0
  je 0
  */
  const byte start_loop_code[] = { 0x4E, 0x8D, 0x14, 0x87, 0x49, 0x8B, 0x02, 0x48, 0x83, 0xF8, 0x00, 0x0F, 0x84, 0x00, 0x00, 0x00, 0x00 };
  const uint start_loop_code_size = sizeof(start_loop_code) / sizeof(byte);
  
  /*
  lea r10, [rdi+r8*4]
  mov rax, [r10]
  jne 0
  */
  const byte stop_loop_code[] = { 0x4E, 0x8D, 0x14, 0x87, 0x49, 0x8B, 0x02, 0x48, 0x83, 0xF8, 0x00, 0x0F, 0x85, 0x00, 0x00, 0x00, 0x00 };
  const uint stop_loop_code_size = sizeof(stop_loop_code) / sizeof(byte);
  
  uint cs = 0; // code Size
  uint linkerStack = 0;
  int jmpTo = 0;
  
  memcpy(&code[0], init_code, init_code_size);
  cs += init_code_size;
  
  for(uint i = 0; i < bfCodeSize; ++i) {
    link* l = &linker[linkerStack];
    switch(bfCode[i]) {
      case '+':
        ++l->instructions;
        memcpy(&code[cs], add_code, add_code_size);
        cs += add_code_size;
        break;
      case '-':
        ++l->instructions;
        memcpy(&code[cs], sub_code, sub_code_size);
        cs += sub_code_size;
        break;
      case '>':
        ++l->instructions;
        memcpy(&code[cs], rdata_code, rdata_code_size);
        cs += rdata_code_size;
        break;
      case '<':
        ++l->instructions;
        memcpy(&code[cs], ldata_code, ldata_code_size);
        cs += ldata_code_size;
        break;
      case ',': 
        ++l->instructions;
        memcpy(&code[cs], input_code, input_code_size);
        cs += input_code_size;
        break;
      case '[':
        memcpy(&code[cs], start_loop_code, start_loop_code_size);
        cs += start_loop_code_size;
        
        l = &linker[++linkerStack];
        l->jmpTo = cs;
        l->instructions = 0;
        break;
      case ']':
        memcpy(&code[cs], stop_loop_code, stop_loop_code_size);
        
        jmpTo = l->jmpTo - (cs + stop_loop_code_size);
        code[cs + stop_loop_code_size - 4] = jmpTo & 0x000000FF;
        code[cs + stop_loop_code_size - 3] = (jmpTo & 0x0000FF00) >> 8;
        code[cs + stop_loop_code_size - 2] = (jmpTo & 0x00FF0000) >> 16;
        code[cs + stop_loop_code_size - 1] = (jmpTo & 0xFF000000) >> 24;
        
        jmpTo = cs - l->jmpTo;
        code[l->jmpTo - 4] = jmpTo & 0x000000FF;
        code[l->jmpTo - 3] = (jmpTo & 0x0000FF00) >> 8;
        code[l->jmpTo - 2] = (jmpTo & 0x00FF0000) >> 16;
        code[l->jmpTo - 1] = (jmpTo & 0xFF000000) >> 24;
        --linkerStack;
        
        cs += stop_loop_code_size;
        break;
    }
  }
  memcpy(&code[cs], exit_code, exit_code_size);
  cs += exit_code_size;
  
  hexDump(code, cs);
  return cs;
}

int main() {
  void* codeMem = mmap(NULL, 4096 * 5, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
  
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
    
    printf("data[0] = %u\n", data[0]);
  }
  return 0;
}
