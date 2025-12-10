#include <unistd.h>
#include <stdio.h>

int main() 
{
        asm volatile(
                "mov %0, %%rdi"
                :
                : "r"(0xEB9F)
                : "rdi"
                );
        printf("pid=%d\n", getpid());
        return 0;
}