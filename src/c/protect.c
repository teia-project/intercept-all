#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>
// just testing if i can actually change perms on a region of memory

int main() {
  void *ptr = mmap(NULL, 4096, PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  printf("mprotect() -> %d, %s\n", mprotect(ptr, 4096, PROT_WRITE), strerror(errno));
  return 0;
}