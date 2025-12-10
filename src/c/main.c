#include <unistd.h>
#include <stdio.h>

int main() 
{
        asm volatile(
                "movq %0, %%rdi"
                :
                : "r"(0xEB9Ful)
                : "rdi"
                );
        printf("pid=%d\n", getpid());
        return 0;
}