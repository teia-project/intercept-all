#ifndef COMMON_H
#define COMMON_H

#include "vmlinux.h"
#include <bpf/bpf_core_read.h>
#include <bpf/bpf_endian.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>

struct bpf_cgroup_syscall_getpid {
  __s32 ret;
};

struct bpf_cgroup_syscall_enter {
        __u64 nr;
        char donthavethelayoutforthisyet[100];
};

#endif