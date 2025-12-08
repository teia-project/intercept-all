bpftool cgroup detach /sys/fs/cgroup cgroup_syscall_getpid pinned /sys/fs/bpf/bpf_getpid
rm -r /sys/fs/bpf/bpf_getpid