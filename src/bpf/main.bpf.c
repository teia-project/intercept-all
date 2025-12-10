#include "common.h"

enum syscall_arg {
        __eps_arg0 = 0,
        __eps_arg1 = 1,
        __eps_arg2 = 2,
        __eps_arg3 = 3,
        __eps_arg4 = 4,
        __eps_arg5 = 5,
        __eps_ret = 6
};

#define EPS_ASSIGN_SCRATCH_PTR(ctx, reg, off) \
        ctx->reg = off; \
        ctx->resolve_ptr_regs |= ((__u8)1 << __eps_##reg)

#define SYS_OPEN 257

int sys_open(struct bpf_cg_syscall_enter *ctx)
{
        char const *path = (char const *)ctx->arg0;
        char const stupid_path[19] = "eps-is-not-general";
        for (int i = 0; i < 19; ++i) {
                char ch;
                if (bpf_probe_read_user((void *)&ch, 1, (void *)(path + i)) < 0) return 1;
                if (stupid_path[i] != ch) {
                        return 1;
                }
        }
        bpf_printk("found file named something stupid!");
        char const clever_path[16] = "eps-is-general\0";
        ctx->scratch[0] = *(__u64 *)&clever_path[0];
        ctx->scratch[1] = *(__u64 *)&clever_path[8];
        EPS_ASSIGN_SCRATCH_PTR(ctx, arg1, 0);
        return 1;
}

SEC("cgroup/syscall_enter")
int bpf_syscall_enter(struct bpf_cg_syscall_enter *ctx)
{
        switch (ctx->nr) {
                case SYS_OPEN:
                        bpf_printk("SYS OPEN\n");
                        return sys_open(ctx);
                default:
                        return 1;
        }

        // if (ctx->nr != 49) { // bind
        //         return 1;
        // }
        // bpf_printk("Definitely got here :/\n");

        // struct sockaddr_in addr;
        // if (bpf_probe_read_user(&addr, sizeof(addr), (void *)ctx->arg1) < 0) {
        //         bpf_printk("failed the readuser\n");
        //         return 0;
        // }
        // ctx->arg1 = 16;
        // for (size_t i = 0; i < sizeof(struct sockaddr_in); ++i) {
        //         ((char *)ctx->scratch)[16 + i] = 0;
        // }
        // ctx->resolve_ptr_regs = 0b10;

        // bpf_printk("nr=%lu\n", ctx->nr);
                
        // bpf_printk("arg0=%llu\n", ctx->arg0);
        // bpf_printk("ctx->arg1=%zx\n", ctx->arg1);
        // bpf_printk("ctx->arg2=%llu\n", ctx->arg2);

        

        // bpf_printk("sin_family=%u\n", addr.sin_family);
        // bpf_printk("sin_addr=%u\n", bpf_ntohl(addr.sin_addr.s_addr));
        // bpf_printk("sin_port=%u\n", bpf_ntohs(addr.sin_port));

        return 1;
}

char LICENSE[] SEC("license") = "GPL";