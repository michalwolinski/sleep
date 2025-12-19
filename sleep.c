#include "syscalls.h"

#define STDOUT 1
#define STDERR 2
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

static inline long strlen(const char *str) {
    long len = 0;
    while (*str++) len++;
    return len;
}

static inline long atoi(const char *str) {
    long res = 0;
    while (*str >= '0' && *str <= '9') {
        res = res * 10 + (*str++ - '0');
    }
    return res;
}

static inline void print(int fd, const char *msg) {
    syscall(SYS_WRITE, fd, (long)msg, strlen(msg));
}

static inline void sleep(long sec) {
    long ms = sec * 1000;
    long ret = syscall(SYS_POLL, 0, 0, ms);

    if (ret < 0) {
        print(STDERR, "Syscall failed.\n");
    }
}

static inline void exit(int code) {
    syscall(SYS_EXIT, code, 0, 0);
}

void _start(long _in_argc, char **_in_argv) {
    long argc;
    char **argv;

    FETCH_ARGS(argc, argv, _in_argc, _in_argv);

    if (argc < 2) {
        print(STDERR, "Usage: ./sleep <seconds>\n");
        exit(EXIT_FAILURE);
    }

    char *arg = argv[1];
    long seconds = atoi(arg);

    if (seconds <= 0) {
        print(STDERR, "Error: Positive integer required.\n");
        exit(EXIT_FAILURE);
    }

    sleep(seconds);

    exit(EXIT_SUCCESS);
}