#include "common.h"

static __always_inline __u64 load_u64(const char *data, int off)
{
    return ((__u64)(unsigned char)data[off + 0])        |
           ((__u64)(unsigned char)data[off + 1] << 8)  |
           ((__u64)(unsigned char)data[off + 2] << 16) |
           ((__u64)(unsigned char)data[off + 3] << 24) |
           ((__u64)(unsigned char)data[off + 4] << 32) |
           ((__u64)(unsigned char)data[off + 5] << 40) |
           ((__u64)(unsigned char)data[off + 6] << 48) |
           ((__u64)(unsigned char)data[off + 7] << 56);
}

SEC("cgroup/syscall_enter")
int bpf_syscall_enter(struct bpf_cg_syscall_enter *ctx)
{
        bpf_printk("nr=%lu\n", ctx->nr);
        
        __u64 r15 = load_u64(ctx->regs_data, 0);
        bpf_printk("r15=%llu\n", r15);

        __u64 di = load_u64(ctx->regs_data, 14);
        bpf_printk("di=%llu\n", di);

        int dix = (__s32)(di & 0xffffffff);
        bpf_printk("di (32bit)=%d\n", dix);

        return 1;
}

char LICENSE[] SEC("license") = "GPL";