#include "common.h"
#include "vmlinux.h"
#include <sys/syscall.h>
#include <sys/time.h>

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
        char const *path = (char const *)ctx->arg1;
        char const stupid_path[19] = "eps-is-not-general";
        for (int i = 0; i < 19; ++i) {
                char ch;
                if (bpf_probe_read_user((void *)&ch, 1, (void *)(path + i)) < 0) return 1;
                if (stupid_path[i] != ch) {
                        return 1;
                }
        }
        bpf_printk("found file named something stupid!");
        char const clever_path[15] = "eps-is-general";
        for (int i = 0; i < 15; ++i) {
                ctx->scratch[i] = clever_path[i];
        }
        EPS_ASSIGN_SCRATCH_PTR(ctx, arg1, 0);
        return 1;
}

int sys_gettimeofday_enter(struct bpf_cg_syscall_enter *ctx)
{
        // stow the original userpsace pointer in scratch[0..8]
        unsigned long uptr = 0;
        for (int i = 0; i < 8; ++i) {
                ctx->scratch[i] = ((char *)&uptr)[i];
        }
        // tell EPS to write to scratch[8] instead
        EPS_ASSIGN_SCRATCH_PTR(ctx, arg0, 8); 
        return 1;
}

int sys_gettimeofday_exit(struct bpf_cg_syscall_enter *ctx)
{
        // first get the userspace pointer we stowed in scratch
        struct timeval *uptr;
        for (int i = 0; i < 8; ++i) {
                ((char *)&uptr)[i] = ctx->scratch[i];
        }
        // then copy the output of the actual syscall
        struct timeval tv;
        for (int i = 8; i < sizeof(struct timeval); ++i) {
                ((char *)&tv)[i] = ctx->scratch[i];
        }
        // then copy it back to userspace
        btf_bpf_probe_write_user((void *)uptr, sizeof(struct timeval), (void *)&tv);
        return 1;
}

SEC("cgroup/syscall_enter")
int bpf_syscall_enter(struct bpf_cg_syscall_enter *ctx)
{
        int flags = 0; 
        // if this is the first time we call a syscall, update this
        if (active_eps_hooks[0] == 0xffffffffffffffff) {
                for (int i = 0; i < 8; ++i) {
                        ctx->active_eps_hooks[i] = 0;
                }
                ctx->active_eps_hooks[1] = 1ul << (96 - 63);
                flags |= 4;
                bpf_printk("update singleton");
        }
        // main switch
        switch (ctx->nr) {
                case SYS_gettimeofday:
                        bpf_printk("SYS_gettimeofday enter\n");
                        return flags | sys_gettimeofday_enter(ctx);
                default:
                        return 1;
        }
        return 1;
}

SEC("group/syscall_exit")
int bpf_syscall_exit(struct bpf_cg_syscall_enter *ctx)
{
        switch (ctx->nr) {
                case SYS_gettimeofday:
                        bpf_printk("SYS_gettimeofday exit\n");
                        return sys_gettimeofday_exit(ctx);
                default:
                        return 1;
        }
        return 1;
}

char LICENSE[] SEC("license") = "GPL";