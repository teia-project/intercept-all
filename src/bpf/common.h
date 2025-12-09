#ifndef COMMON_H
#define COMMON_H

#include "vmlinux.h"
#include <bpf/bpf_core_read.h>
#include <bpf/bpf_endian.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>

struct bpf_cg_syscall_enter {
	unsigned int nr;
	unsigned long arg0, arg1, arg2, arg3, arg4, arg5, ret;
	__u8 resolve_ptr_regs;
	__u64 scratch[128];
};

#endif