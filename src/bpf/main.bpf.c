#include "common.h"

// static __always_inline __u64 load_u64(const char *data, int off)
// {
//     return ((__u64)(unsigned char)data[(off * 8) + 0])        |
//            ((__u64)(unsigned char)data[(off * 8) + 1] << 8)  |
//            ((__u64)(unsigned char)data[(off * 8) + 2] << 16) |
//            ((__u64)(unsigned char)data[(off * 8) + 3] << 24) |
//            ((__u64)(unsigned char)data[(off * 8) + 4] << 32) |
//            ((__u64)(unsigned char)data[(off * 8) + 5] << 40) |
//            ((__u64)(unsigned char)data[(off * 8) + 6] << 48) |
//            ((__u64)(unsigned char)data[(off * 8) + 7] << 56);
// }

SEC("cgroup/syscall_enter")
int bpf_syscall_enter(struct bpf_cg_syscall_enter *ctx)
{
        if (ctx->nr != 49) {
                return 1;
        }

        bpf_printk("nr=%lu\n", ctx->nr);
                
        bpf_printk("arg0=%llu\n", ctx->arg0);
        bpf_printk("ctx->arg1=%zx\n", ctx->arg1);
        bpf_printk("ctx->arg2=%llu\n", ctx->arg2);

        struct sockaddr_in addr;
        if (bpf_probe_read_user(&addr, sizeof(addr), (void *)ctx->arg1) < 0) {
                return 0;
        }

        bpf_printk("sin_family=%u\n", addr.sin_family);
        bpf_printk("sin_addr=%u\n", bpf_ntohl(addr.sin_addr.s_addr));
        bpf_printk("sin_port=%u\n", bpf_ntohs(addr.sin_port));

        return 1;
}

char LICENSE[] SEC("license") = "GPL";