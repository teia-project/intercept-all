#include "common.h"

SEC("cgroup/syscall_enter")
int bpf_syscall_enter(struct bpf_cgroup_syscall_enter *ctx)
{
        bpf_printk("syscall(%lu)\n", ctx->nr);
        return 1 | 2;
}

char LICENSE[] SEC("license") = "GPL";