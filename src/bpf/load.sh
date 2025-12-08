bpftool prog loadall build/main.bpf.o /sys/fs/bpf/
bpftool cgroup attach /sys/fs/cgroup cgroup_syscall_enter pinned /sys/fs/bpf/bpf_getpid