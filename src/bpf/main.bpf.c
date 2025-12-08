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
        bpf_printk("nr=%lu\n", ctx->nr);
        
        __u64 r15 = load_u64(ctx->regs_data, 0);
        bpf_printk("r15=%llu\n", r15);

        __u64 di = load_u64(ctx->regs_data, 14);
        bpf_printk("di=%llu\n", di);

        bpf_printk("di bytes: %u %u %u %u %u %u %u %u\n",
           (unsigned char)ctx->regs_data[112+0],
           (unsigned char)ctx->regs_data[112+1],
           (unsigned char)ctx->regs_data[112+2],
           (unsigned char)ctx->regs_data[112+3],
           (unsigned char)ctx->regs_data[112+4],
           (unsigned char)ctx->regs_data[112+5],
           (unsigned char)ctx->regs_data[112+6],
           (unsigned char)ctx->regs_data[112+7]);

        return 1;
}

char LICENSE[] SEC("license") = "GPL";