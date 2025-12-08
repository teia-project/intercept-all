#include "common.h"

static __always_inline __u64 load_u64(const char *data, int off)
{
    return ((__u64)(unsigned char)data[(off * 8) + 0])        |
           ((__u64)(unsigned char)data[(off * 8) + 1] << 8)  |
           ((__u64)(unsigned char)data[(off * 8) + 2] << 16) |
           ((__u64)(unsigned char)data[(off * 8) + 3] << 24) |
           ((__u64)(unsigned char)data[(off * 8) + 4] << 32) |
           ((__u64)(unsigned char)data[(off * 8) + 5] << 40) |
           ((__u64)(unsigned char)data[(off * 8) + 6] << 48) |
           ((__u64)(unsigned char)data[(off * 8) + 7] << 56);
}

SEC("cgroup/syscall_enter")
int bpf_syscall_enter(struct bpf_cg_syscall_enter *ctx)
{
        if (ctx->nr != 49) {
                return 1;
        }

        bpf_printk("nr=%lu\n", ctx->nr);
        
        __u64 arg1 = load_u64(ctx->regs_data, 14);
        bpf_printk("arg1=%llu\n", arg1);
        
        __u64 arg2 = load_u64(ctx->regs_data, 13);
        bpf_printk("arg2=%llu\n", arg2);

        __u64 arg3 = load_u64(ctx->regs_data, 12);
        bpf_printk("arg3=%llu\n", arg3);

        // ((volatile unsigned char *)&ctx->regs_data[112])[0] = 0;

        return 1;
}

char LICENSE[] SEC("license") = "GPL";