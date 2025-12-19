# sleep

A minimal, zero-dependency implementation of the `sleep` command in C, written without the standard library (`libc`).

## Features

- **No Dependencies**: Does not link against `libc` or `libSystem`.
- **Tiny Footprint**: Compiled binary is extremely small.
- **Cross-Platform**: Supports Linux (x86_64) and macOS (Apple Silicon/ARM64).
- **Pure C**: Uses inline assembly for direct system calls.

## Building

Requires `gcc` (Linux) or `clang` (macOS).

```sh
make
```

## Usage
```sh
./sleep <seconds>
```

## Architecture

The project separates hardware abstraction from logic:
- sleep.c: Main logic, argument parsing, string manipulation.
- syscalls.h: OS-specific system call wrappers (Linux syscall / macOS svc).

## Author

Michal Wolinski