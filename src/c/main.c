// #include <fcntl.h>
// #include <stdio.h>
// #include <string.h>
// #include <sys/syscall.h>
// #include <unistd.h>

// static inline unsigned long rdi(void) {
//   unsigned long val;
//   asm volatile("mov %%rdi, %0" : "=r"(val));
//   return val;
// }

// static inline unsigned long rsi(void) {
//   unsigned long val;
//   asm volatile("mov %%rsi, %0" : "=r"(val));
//   return val;
// }

// int main() {
//   char const *path = "eps-is-not-general";
//   printf("path(before)=%p\n", path);
//   int flags = O_WRONLY | O_CREAT | O_TRUNC;
//   int perms = 0644;
//   long fd;
//   asm volatile("mov %[perms], %%r10\n\t" // 4th arg
//                "mov %[nr], %%rax\n\t"    // syscall number
//                "syscall"
//                : "=a"(fd)
//                : [nr] "i"(SYS_openat),
//                  "D"(AT_FDCWD), // 1st arg
//                  "S"(path),     // 2nd arg
//                  "d"(flags),    // 3rd arg
//                  [perms] "r"((long)perms)
//                : "rcx", "r11", "r10", "memory");
//   if (fd < 0)
//     return 1;
//   path = (char const *)rsi();
//   printf("path(after) =%p\n", path);

//   void *page = (void *)((unsigned long)path & ~0xfff);

//   const char *msg = "I think I can get away with naming files lies\n";
//   write(fd, msg, strlen(msg));

//   close(fd);
//   return 0;
// }

#include <stdio.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

int main(void) {
  struct timeval tv;
  struct tm tm;

  /* direct system call */
  if (syscall(SYS_gettimeofday, &tv, NULL) < 0)
    return 1;

  /* convert to broken-down time */
  if (!localtime_r(&tv.tv_sec, &tm))
    return 1;

  printf("%04d-%02d-%02d %02d:%02d:%02d.%06ld\n", tm.tm_year + 1900,
         tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec,
         (long)tv.tv_usec);

  return 0;
}
