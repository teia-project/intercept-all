bpftool cgroup detach /sys/fs/cgroup cgroup_syscall_enter pinned /sys/fs/bpf/bpf_syscall_enter
rm -r /sys/fs/bpf/bpf_syscall_enter