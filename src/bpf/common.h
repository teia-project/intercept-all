#ifndef COMMON_H
#define COMMON_H

#include "vmlinux.h"
#include <bpf/bpf_core_read.h>
#include <bpf/bpf_endian.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>

struct bpf_cg_syscall_enter {
	unsigned int nr;
	// these are the syscall arguments, e.g. in x64 this would be
	// rdi, rsi, rdx, r10, r8, r9, rax.
	unsigned long arg0, arg1, arg2, arg3, arg4, arg5, ret;
	// Linux has at most 7 arg registers + 2 return registers. (we just have
	// one ret register). Set the nth bit to 1 to resolve the offset into
	// scratch stored in this register to be a true pointer
	__u8 resolve_ptr_regs;
        __u8 _padding[7];
	// 4096 bytes of (protected) scratch memory exposed to the ebpf program
	// we have to convert offsets into this scratch to actual pointers
	// after we return control to the kernel, to do this we use
	// `resolve_ptr_regs`.
	char scratch[4096];
        __u64 active_eps_hooks[8];
};


#endif