<div align="center">

# uuid

<a href="https://muhammad-fiaz.github.io/uuid/"><img src="https://img.shields.io/badge/docs-muhammad--fiaz.github.io-blue" alt="Documentation"></a>
<a href="https://github.com/muhammad-fiaz/uuid"><img src="https://img.shields.io/badge/C-C99%20%7C%20C11%20%7C%20C17%20%7C%20C23-blue.svg?logo=c" alt="C Standard"></a>
<a href="https://github.com/muhammad-fiaz/uuid"><img src="https://img.shields.io/github/stars/muhammad-fiaz/uuid" alt="GitHub stars"></a>
<a href="https://github.com/muhammad-fiaz/uuid/issues"><img src="https://img.shields.io/github/issues/muhammad-fiaz/uuid" alt="GitHub issues"></a>
<a href="https://github.com/muhammad-fiaz/uuid/pulls"><img src="https://img.shields.io/github/issues-pr/muhammad-fiaz/uuid" alt="GitHub pull requests"></a>
<a href="https://github.com/muhammad-fiaz/uuid"><img src="https://img.shields.io/github/last-commit/muhammad-fiaz/uuid" alt="GitHub last commit"></a>
<a href="https://github.com/muhammad-fiaz/uuid"><img src="https://img.shields.io/github/license/muhammad-fiaz/uuid" alt="License"></a>
<a href="https://github.com/muhammad-fiaz/uuid/actions/workflows/ci.yml"><img src="https://github.com/muhammad-fiaz/uuid/actions/workflows/ci.yml/badge.svg" alt="CI"></a>
<img src="https://img.shields.io/badge/platforms-linux%20%7C%20windows%20%7C%20macos%20%7C%20android%20%7C%20ios%20%7C%20freebsd-blue" alt="Supported Platforms">
<a href="https://github.com/muhammad-fiaz/uuid/releases/latest"><img src="https://img.shields.io/github/v/release/muhammad-fiaz/uuid?label=Latest%20Release&style=flat-square" alt="Latest Release"></a>
<a href="https://github.com/sponsors/muhammad-fiaz"><img src="https://img.shields.io/badge/Sponsor-GitHub-pink?style=social&logo=github" alt="GitHub Sponsors"></a>
<a href="https://hits.sh/github.com/muhammad-fiaz/uuid/"><img src="https://hits.sh/github.com/muhammad-fiaz/uuid.svg?label=Visitors&extraCount=0&color=green" alt="Repo Visitors"></a>

<p><em>A production-grade UUID library for C/C++ implementing RFC 9562.</em></p>

<b><a href="https://muhammad-fiaz.github.io/uuid/">Documentation</a> |
<a href="https://muhammad-fiaz.github.io/uuid/api/overview">API Reference</a> |
<a href="https://muhammad-fiaz.github.io/uuid/guide/getting-started">Quick Start</a> |
<a href="CONTRIBUTING.md">Contributing</a></b>

</div>

`uuid` is a production-grade, self-contained UUID library for C and C++. It implements all UUID versions defined by RFC 9562, uses zero third-party runtime dependencies, and supports C99 through C23 and C++98 through C++23.

> [!TIP]
> If you build with uuid, make sure to give it a star.

> [!NOTE]
> **Cross-platform:** uuid supports Linux (GCC, Clang), Windows (MSVC 2015+), macOS (Clang), Android, iOS, FreeBSD, OpenBSD, and NetBSD with zero external dependencies. C99 or later required, C++ fully supported.

---

<details>
<summary><strong>Features</strong> (click to expand)</summary>

| Feature | Description | Documentation |
|---------|-------------|---------------|
| **UUID v1** | Time-based (Gregorian epoch) with monotonic counter | https://muhammad-fiaz.github.io/uuid/uuid/v1 |
| **UUID v3** | Name-based (MD5) with well-known namespaces | https://muhammad-fiaz.github.io/uuid/uuid/v3 |
| **UUID v4** | Cryptographically secure random | https://muhammad-fiaz.github.io/uuid/uuid/v4 |
| **UUID v5** | Name-based (SHA-1) with well-known namespaces | https://muhammad-fiaz.github.io/uuid/uuid/v5 |
| **UUID v6** | Reordered time-based (Gregorian, sortable) | https://muhammad-fiaz.github.io/uuid/uuid/v6 |
| **UUID v7** | Unix epoch time-based, millisecond precision | https://muhammad-fiaz.github.io/uuid/uuid/v7 |
| **UUID v8** | Custom/vendor-specific with version/variant bits | https://muhammad-fiaz.github.io/uuid/uuid/v8 |
| **Nil/Max UUID** | Well-known sentinel UUIDs | https://muhammad-fiaz.github.io/uuid/uuid/special |
| **Parsing** | Canonical, compact, braced, mixed case, strict/relaxed | https://muhammad-fiaz.github.io/uuid/api/parsing |
| **Formatting** | Canonical, compact, braced, uppercase, binary | https://muhammad-fiaz.github.io/uuid/api/formatting |
| **Validation** | Full RFC compliance checking | https://muhammad-fiaz.github.io/uuid/api/validation |
| **Comparison** | Byte-order comparison, qsort-compatible | https://muhammad-fiaz.github.io/uuid/api/comparison |
| **Sorting** | Ascending/descending sort for arrays | https://muhammad-fiaz.github.io/uuid/api/sorting |
| **Hashing** | FNV-1a hash for hash tables, MD5, SHA-1 | https://muhammad-fiaz.github.io/uuid/api/hashing |
| **Serialization** | Binary serialization/deserialization | https://muhammad-fiaz.github.io/uuid/api/serialization |
| **Namespaces** | DNS, URL, OID, X500 well-known namespaces | https://muhammad-fiaz.github.io/uuid/uuid/namespaces |
| **Thread Safety** | Thread-local state, no global mutable state | https://muhammad-fiaz.github.io/uuid/guide/thread-safety |
| **Cross-Platform** | Linux, Windows, macOS, Android, iOS, FreeBSD | https://muhammad-fiaz.github.io/uuid/guide/platforms |
| **Zero Dependencies** | Only standard C library + OS random APIs | https://muhammad-fiaz.github.io/uuid/guide/installation |
| **C++ Compatible** | extern "C" support, compiles with C++98-23 | https://muhammad-fiaz.github.io/uuid/guide/cpp-compat |

</details>

---

<details>
<summary><strong>Prerequisites and Supported Platforms</strong> (click to expand)</summary>

<br>

## Prerequisites

| Requirement | Version | Notes |
|-------------|---------|-------|
| **C Compiler** | C99 or later (GCC 4.8+, Clang 3.0+, MSVC 2015+) | Supports C99, C11, C17, C23 |
| **CMake** | 3.14+ | Build system |
| **Meson** | 0.56+ | Alternative build system |

---

## Supported Platforms

| Platform | x86_64 | ARM64 | ARM | RISC-V |
|----------|--------|-------|-----|--------|
| **Linux** | Yes | Yes | Yes | Yes |
| **Windows** | Yes | Yes | Yes | - |
| **macOS** | Yes | Yes (Apple Silicon) | - | - |
| **Android** | Yes | Yes | Yes | - |
| **iOS** | - | Yes | Yes | - |
| **FreeBSD** | Yes | Yes | Yes | - |

</details>

---

## Installation

### Method 1: CMake (FetchContent)

```cmake
include(FetchContent)
FetchContent_Declare(uuid
    GIT_REPOSITORY https://github.com/muhammad-fiaz/uuid.git
    GIT_TAG v0.1.0)
FetchContent_MakeAvailable(uuid)
target_link_libraries(your_target PRIVATE uuid::static)
```

### Method 2: CMake (Subdirectory)

```bash
git clone https://github.com/muhammad-fiaz/uuid.git
```

```cmake
add_subdirectory(uuid)
target_link_libraries(your_target PRIVATE uuid::static)
```

### Method 3: Meson

```meson
uuid_dep = dependency('uuid', version: '>=0.1.0')
```

### Method 4: Build from Source

```bash
git clone https://github.com/muhammad-fiaz/uuid.git
cd uuid
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
sudo cmake --install build  # or set CMAKE_INSTALL_PREFIX
```

---

## Quick Start

### C Usage

```c
#include <uuid/uuid.h>
#include <stdio.h>

int main(void) {
    uuid_t uuid;
    char buf[UUID_STRING_LEN];

    /* Generate a random UUID v4 */
    uuid_v4(&uuid);
    uuid_format(&uuid, buf, sizeof(buf));
    printf("Random UUID: %s\n", buf);

    /* Generate a time-based UUID v7 */
    uuid_v7_state_t state;
    uuid_v7_init(&state);
    uuid_v7(&state, &uuid);
    uuid_format(&uuid, buf, sizeof(buf));
    printf("UUID v7:     %s\n", buf);

    /* Parse a UUID */
    uuid_parse(&uuid, "550e8400-e29b-41d4-a716-446655440000");
    printf("Version:     %d\n", uuid_version(&uuid));

    return 0;
}
```

### C Usage (Name-based)

```c
#include <uuid/uuid.h>
#include <stdio.h>

int main(void) {
    uuid_t uuid;
    char buf[UUID_STRING_LEN];

    /* UUID v3 (MD5) with DNS namespace */
    uuid_v3_ns(UUID_NS_DNS, "example.com", 11, &uuid);
    uuid_format(&uuid, buf, sizeof(buf));
    printf("v3: %s\n", buf);

    /* UUID v5 (SHA-1) with DNS namespace */
    uuid_v5_ns(UUID_NS_DNS, "example.com", 11, &uuid);
    uuid_format(&uuid, buf, sizeof(buf));
    printf("v5: %s\n", buf);

    return 0;
}
```

---

## Examples

The `examples/` directory contains **17 comprehensive, runnable examples**:

| Example | Description | Documentation |
|---------|-------------|---------------|
| [`basic`](examples/basic.c) | Generate, parse, format, hash | https://muhammad-fiaz.github.io/uuid/examples/basic |
| [`v1`](examples/v1.c) | Time-based UUID with timestamp extraction | https://muhammad-fiaz.github.io/uuid/uuid/v1 |
| [`v3`](examples/v3.c) | MD5 name-based with namespaces | https://muhammad-fiaz.github.io/uuid/uuid/v3 |
| [`v4`](examples/v4.c) | Random generation with verification | https://muhammad-fiaz.github.io/uuid/uuid/v4 |
| [`v5`](examples/v5.c) | SHA-1 name-based with namespaces | https://muhammad-fiaz.github.io/uuid/uuid/v5 |
| [`v6`](examples/v6.c) | Reordered time-based | https://muhammad-fiaz.github.io/uuid/uuid/v6 |
| [`v7`](examples/v7.c) | Unix epoch time-based, monotonic | https://muhammad-fiaz.github.io/uuid/uuid/v7 |
| [`v8`](examples/v8.c) | Custom/vendor-specific UUIDs | https://muhammad-fiaz.github.io/uuid/uuid/v8 |
| [`parsing`](examples/parsing.c) | All parsing formats and validation | https://muhammad-fiaz.github.io/uuid/api/parsing |
| [`formatting`](examples/formatting.c) | All formatting options | https://muhammad-fiaz.github.io/uuid/api/formatting |
| [`validation`](examples/validation.c) | Input validation | https://muhammad-fiaz.github.io/uuid/api/validation |
| [`comparison`](examples/comparison.c) | Comparison and sorting | https://muhammad-fiaz.github.io/uuid/api/comparison |
| [`serialization`](examples/serialization.c) | Binary serialization | https://muhammad-fiaz.github.io/uuid/api/serialization |
| [`custom_uuid`](examples/custom_uuid.c) | Custom UUID creation with version/variant bits | https://muhammad-fiaz.github.io/uuid/uuid/v8 |
| [`binary_conversion`](examples/binary_conversion.c) | UUID binary serialization and conversion | https://muhammad-fiaz.github.io/uuid/api/serialization |
| [`threading`](examples/threading.c) | Thread-safe generation | https://muhammad-fiaz.github.io/uuid/guide/thread-safety |
| [`error_handling`](examples/error_handling.c) | Error codes and messages | https://muhammad-fiaz.github.io/uuid/api/errors |

To run any example:

```bash
cmake -B build -DUUID_BUILD_EXAMPLES=ON -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
./build/examples/example_basic
```

---

## Build Options

| Option | Default | Description |
|--------|---------|-------------|
| `UUID_BUILD_SHARED` | ON | Build shared library |
| `UUID_BUILD_STATIC` | ON | Build static library |
| `UUID_BUILD_TESTS` | OFF | Build unit tests |
| `UUID_BUILD_EXAMPLES` | OFF | Build examples |
| `UUID_BUILD_BENCHMARKS` | OFF | Build benchmarks |
| `UUID_WERROR` | OFF | Treat warnings as errors |

---

## Testing

Run the full test suite:

```bash
cmake -B build -DUUID_BUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

---

## Benchmarks

Run benchmarks on your own machine:

```bash
cmake -B build -DUUID_BUILD_BENCHMARKS=ON -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
./build/benchmarks/bench_uuid
```

### Example Results (Linux x64, GCC 13, 100,000 iterations)

| Operation | Throughput |
|-----------|------------|
| v4 generate | ~500K ops/sec |
| v7 generate | ~400K ops/sec |
| v1 generate | ~400K ops/sec |
| v5 generate (DNS) | ~300K ops/sec |
| parse | ~600K ops/sec |
| format | ~700K ops/sec |
| compare | ~2M ops/sec |

---

## Contributing

Contributions are welcome! Please:

1. Fork the repository
2. Create a feature branch
3. Add tests for new functionality
4. Ensure all tests pass
5. Submit a pull request

See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

---

## License

MIT License - Copyright (c) 2026 Muhammad Fiaz - see [LICENSE](LICENSE) for details.
