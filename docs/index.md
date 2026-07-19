---
layout: home
hero:
  name: uuid
  text: Production-grade UUID Library for C/C++
  tagline: A complete, self-contained RFC 9562 UUID library. Zero dependencies. C99-C23. Cross-platform.
  image:
    src: /logo.svg
    alt: uuid
  actions:
    - theme: brand
      text: Get Started
      link: /guide/getting-started
    - theme: alt
      text: API Reference
      link: /api/overview
    - theme: alt
      text: GitHub
      link: https://github.com/muhammad-fiaz/uuid

features:
  - title: RFC 9562 Complete
    details: Full implementation of UUID v1, v3, v4, v5, v6, v7, v8, Nil UUID, and Max UUID. Every version is production-ready.
  - title: Zero Dependencies
    details: No third-party runtime dependencies. Only uses standard C library and native OS random APIs.
  - title: Cross-Platform
    details: Linux, Windows, macOS, Android, iOS, FreeBSD. x86, x64, ARM, ARM64, RISC-V. 32-bit and 64-bit.
  - title: C & C++ Compatible
    details: Compiles cleanly under C99, C11, C17, C23. Full extern "C" support for C++98 through C++23.
  - title: Thread Safe
    details: Thread-local state, no global mutable state. Safe for concurrent use from multiple threads.
  - title: High Performance
    details: Optimized generation, parsing, and formatting. Cryptographically secure random generation.
---
