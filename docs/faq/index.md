# FAQ

Frequently asked questions about the uuid library.

## General

### What is uuid?

uuid is a production-grade UUID library for C/C++ implementing RFC 9562. It supports all UUID versions (v1, v3, v4, v5, v6, v7, v8) with zero third-party runtime dependencies.

### What license is uuid under?

MIT License. See [LICENSE](https://github.com/muhammad-fiaz/uuid/blob/main/LICENSE).

### What C standard is required?

C99 or later. Supports C99, C11, C17, and C23.

### Does it work with C++?

Yes. Headers include `extern "C"` guards and compile cleanly with C++98 through C++23.

## Technical

### Which UUID version should I use?

| Use Case | Version |
|----------|---------|
| General unique ID | v4 |
| Database primary key | v7 |
| Time-sortable ID | v7 |
| Deterministic from name | v5 |
| Legacy compatibility | v1 |
| Custom format | v8 |

### Is the random number generation secure?

Yes. Uses `getrandom()` (Linux), `BCryptGenRandom()` (Windows), `arc4random_buf()` (macOS). All are cryptographically secure.

### Is the library thread safe?

Yes. All public API functions are thread-safe. Thread-local state is used for convenience functions.

### Are there any heap allocations?

Only for UUID v3 and v5 (name-based), which need a temporary buffer for the namespace + name concatenation. All other operations are allocation-free.

### How do I use this in embedded systems?

Use the static library. The only heap allocation path is for v3/v5. Use v4, v7, or v8 for allocation-free operation.

## Building

### How do I build with CMake?

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### How do I run tests?

```bash
cmake -B build -DUUID_BUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build
```

### How do I run benchmarks?

```bash
cmake -B build -DUUID_BUILD_BENCHMARKS=ON -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/benchmarks/bench_uuid
```
