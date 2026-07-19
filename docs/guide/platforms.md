# Supported Platforms

The uuid library supports a wide range of platforms and architectures.

## Operating Systems

| OS | Status | Notes |
|----|--------|-------|
| Linux | Supported | getrandom(), /dev/urandom fallback |
| Windows | Supported | BCryptGenRandom() |
| macOS | Supported | arc4random_buf() |
| Android | Supported | getrandom() |
| iOS | Supported | arc4random_buf() |
| FreeBSD | Supported | getrandom() |
| OpenBSD | Supported | getrandom() |
| NetBSD | Supported | getrandom() |

## Architectures

| Architecture | Status |
|-------------|--------|
| x86 (32-bit) | Supported |
| x86_64 (64-bit) | Supported |
| ARM (32-bit) | Supported |
| ARM64 (64-bit) | Supported |
| RISC-V | Supported |

## Compilers

| Compiler | Minimum Version | Status |
|----------|----------------|--------|
| GCC | 4.8+ | Supported |
| Clang | 3.0+ | Supported |
| MSVC | 2015+ | Supported |
| Intel oneAPI | Recent | Supported |
| TinyCC | Recent | Supported where practical |

## Byte Order

The library handles endianness correctly:
- Little-endian systems: x86, x86_64, ARM (default), ARM64
- Big-endian systems: ARM (configurable), RISC-V (configurable), PowerPC

## Random Number Generation

| Platform | API Used |
|----------|----------|
| Linux | `getrandom()` with `/dev/urandom` fallback |
| Windows | `BCryptGenRandom()` |
| macOS/iOS | `arc4random_buf()` |
| FreeBSD/OpenBSD/NetBSD | `getrandom()` |
| Other | `rand()` fallback (not cryptographically secure) |

## C Language Standards

| Standard | Status |
|----------|--------|
| C99 | Supported |
| C11 | Supported |
| C17 | Supported |
| C23 | Supported |
