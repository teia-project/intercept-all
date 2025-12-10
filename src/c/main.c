#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

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
  //   asm volatile("movq %0, %%rdi" : : "r"(0xEB9Ful) : "rdi");
  //   volatile int n = getpid();
  //   printf("rdi=%zu, rsi=%zu\n", rdi(), rsi());
  int fd = open("eps-is-not-general", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd < 0)
    return 1;

  const char *msg = "I think I can get away with naming files lies\n";
  write(fd, msg, strlen(msg));

  close(fd);
  return 0;
}