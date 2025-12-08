#include "common.h"

SEC("cgroup/syscall_enter")
int bpf_syscall_enter(struct bpf_cgroup_syscall_enter *ctx)
{
        bpf_printk("nr=%lu\n", ctx->nr);
        return 1;
}

char LICENSE[] SEC("license") = "GPL";