#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/syscall.h>
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
  char const *path = "eps-is-not-general";
  printf("path(before)=%p\n", path);
  int flags = O_WRONLY | O_CREAT | O_TRUNC;
  int perms = 0644;
  long fd;
  asm volatile("mov %[perms], %%r10\n\t" // 4th arg
               "mov %[nr], %%rax\n\t"    // syscall number
               "syscall"
               : "=a"(fd)
               : [nr] "i"(SYS_openat),
                 "D"(AT_FDCWD), // 1st arg
                 "S"(path),     // 2nd arg
                 "d"(flags),    // 3rd arg
                 [perms] "r"((long)perms)
               : "rcx", "r11", "r10", "memory");
  if (fd < 0)
    return 1;
  printf("path(after) =%p\n", (void *)rsi());

  const char *msg = "I think I can get away with naming files lies\n";
  write(fd, msg, strlen(msg));

  close(fd);
  return 0;
}