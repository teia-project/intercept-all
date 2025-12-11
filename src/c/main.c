#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

static int time_gettimeofday(void) {
    const long iterations = (1L << 20);

    volatile struct timeval tv;
    struct timespec start, end;

    if (clock_gettime(CLOCK_MONOTONIC_RAW, &start) != 0)
        return 1;

    for (long i = 0; i < iterations; ++i) {
        if (syscall(SYS_gettimeofday, &tv, NULL) < 0)
            return 1;
    }

    if (clock_gettime(CLOCK_MONOTONIC_RAW, &end) != 0)
        return 1;

    unsigned long long total_ns =
        (unsigned long long)(end.tv_sec - start.tv_sec) * 1000000000ULL +
        (unsigned long long)(end.tv_nsec - start.tv_nsec);

    double avg_ns = (double)total_ns / (double)iterations;

    printf("gettimeofday,%ld,%llu,%.2f\n", iterations, total_ns, avg_ns);
    return 0;
}

static int time_getpid(void) {
    const long iterations = (1L << 20);

    volatile long pid;
    struct timespec start, end;

    if (clock_gettime(CLOCK_MONOTONIC_RAW, &start) != 0)
        return 1;

    for (long i = 0; i < iterations; ++i) {
        pid = syscall(SYS_getpid);
        if (pid <= 0)  // trivial sanity check
            return 1;
    }

    if (clock_gettime(CLOCK_MONOTONIC_RAW, &end) != 0)
        return 1;

    unsigned long long total_ns =
        (unsigned long long)(end.tv_sec - start.tv_sec) * 1000000000ULL +
        (unsigned long long)(end.tv_nsec - start.tv_nsec);

    double avg_ns = (double)total_ns / (double)iterations;

    printf("getpid,%ld,%llu,%.2f\n", iterations, total_ns, avg_ns);
    return 0;
}

static int time_openat(void) {
    const long iterations = (1L << 20);
    const char *path = "example.txt";
    int flags = O_RDONLY;
    struct timespec start, end;

    /*
     * Ensure the file exists once, outside the measurement.
     * This uses the libc wrapper intentionally; only the benchmarked
     * path is forced through syscall().
     */
    int tmp = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (tmp < 0)
        return 1;
    close(tmp);

    if (clock_gettime(CLOCK_MONOTONIC_RAW, &start) != 0)
        return 1;

    for (long i = 0; i < iterations; ++i) {
        volatile long fd = syscall(SYS_openat, AT_FDCWD, path, flags);
        if (fd < 0)
            return 1;
        if (syscall(SYS_close, fd) < 0)
            return 1;
    }

    if (clock_gettime(CLOCK_MONOTONIC_RAW, &end) != 0)
        return 1;

    unsigned long long total_ns =
        (unsigned long long)(end.tv_sec - start.tv_sec) * 1000000000ULL +
        (unsigned long long)(end.tv_nsec - start.tv_nsec);

    double avg_ns = (double)total_ns / (double)iterations;

    printf("openat,%ld,%llu,%.2f\n", iterations, total_ns, avg_ns);
    return 0;
}

int main(void) {
    if (time_gettimeofday() != 0)
        return 1;
    if (time_getpid() != 0)
        return 1;
    if (time_openat() != 0)
        return 1;

    return 0;
}
