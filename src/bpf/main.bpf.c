#include "common.h"

// SEC("cgroup/syscall_enter")
// int bpf_syscall_enter(struct bpf_cgroup_syscall_enter *ctx)
// {
//         bpf_printk("syscall(%lu)\n", ctx->nr);
//         return 1 | 2;
// }

struct bpf_cgroup_syscall_socket {
        __u32 family;
        __u32 type;
        __u32 protocol;
        __u32 ret;
};

SEC("cgroup/syscall_socket")
int bpf_ns_socket(struct bpf_cgroup_syscall_socket *ctx)
{
        return 1 | 2;
}

char LICENSE[] SEC("license") = "GPL";