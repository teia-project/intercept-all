#ifndef COMMON_H
#define COMMON_H

#include "vmlinux.h"
#include <bpf/bpf_core_read.h>
#include <bpf/bpf_endian.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>

struct bpf_cg_syscall_enter {
  unsigned int nr;
  char regs_data[512];
  __s32 ret;
};

#endif