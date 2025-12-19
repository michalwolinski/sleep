#ifndef SYSCALLS_H
#define SYSCALLS_H

#if defined(__linux__) && defined(__x86_64__)

    #define SYS_WRITE     1
    #define SYS_POLL      7
    #define SYS_EXIT      60

    static inline long syscall(long num, long arg1, long arg2, long arg3) {
        long ret;
        __asm__ __volatile__ (
            "syscall"
            : "=a" (ret)
            : "a" (num), "D" (arg1), "S" (arg2), "d" (arg3)
            : "rcx", "r11", "memory"
        );
        return ret;
    }

    #define FETCH_ARGS(argc_out, argv_out, _reg_argc, _reg_argv) do { \
        (void)_reg_argc; \
        (void)_reg_argv; \
        long *sp; \
        __asm__ __volatile__ ("mov %%rsp, %0" : "=r" (sp)); \
        argc_out = sp[0]; \
        argv_out = (char **)(sp + 1); \
    } while(0)

#elif defined(__APPLE__) && defined(__aarch64__)

    #define SYS_WRITE     0x2000004
    #define SYS_POLL      0x20000E6
    #define SYS_EXIT      0x2000001

    static inline long syscall(long num, long arg1, long arg2, long arg3) {
        register long x16 __asm__("x16") = num;
        register long x0  __asm__("x0")  = arg1;
        register long x1  __asm__("x1")  = arg2;
        register long x2  __asm__("x2")  = arg3;

        __asm__ __volatile__ (
            "svc 0"
            : "+r" (x0)
            : "r" (x16), "r" (x1), "r" (x2)
            : "memory", "cc"
        );
        return x0;
    }

    #define FETCH_ARGS(argc_out, argv_out, _reg_argc, _reg_argv) do { \
        argc_out = _reg_argc; \
        argv_out = _reg_argv; \
    } while(0)

#else
    #error "Target architecture not supported"
#endif

#endif