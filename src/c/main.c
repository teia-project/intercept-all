#include <stdio.h>
#include <unistd.h>

static inline unsigned long rdi(void) {
  unsigned long val;
  asm volatile("mov %%rdi, %0" : "=r"(val));
  return val;
}

static inline unsigned long rsi(void) {
  unsigned long val;
  asm volatile("mov %%rsi, %0" : "=r"(val));
  return val;
}

int main() {
  asm volatile("movq %0, %%rdi" : : "r"(0xEB9Ful) : "rdi");
  volatile int n = getpid();
  printf("rdi=%zu, rsi=%zu\n", rdi(), rsi());
  return 0;
}