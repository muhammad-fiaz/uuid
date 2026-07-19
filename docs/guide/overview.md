# Overview

The uuid library provides a complete, self-contained implementation of UUID generation per RFC 9562.

## Architecture

The library is organized into:

- **Public API** (`include/uuid/uuid.h`): All public functions and types
- **Implementation** (`src/uuid.c`): Core implementation
- **Platform Abstraction**: OS-specific random generation and time functions

## Key Design Principles

1. **Zero Dependencies**: Only uses standard C library and native OS APIs
2. **Thread Safety**: Thread-local state, no global mutable state
3. **Memory Safety**: No hidden allocations in hot paths, caller-provided buffers
4. **RFC Compliance**: Full compliance with RFC 9562 for all UUID versions
5. **Performance**: Optimized for generation, parsing, and formatting

## UUID Format

A UUID is a 128-bit identifier represented as:

```
xxxxxxxx-xxxx-Mxxx-Nxxx-xxxxxxxxxxxx
```

Where:
- `M` = Version (4 bits, at byte 6, high nibble)
- `N` = Variant (2 bits, at byte 8, high bits)

## Supported Versions

| Version | Type | Description |
|---------|------|-------------|
| v1 | Time-based | Gregorian epoch, with clock sequence and node |
| v3 | Name-based | MD5 hash of namespace + name |
| v4 | Random | Cryptographically secure random |
| v5 | Name-based | SHA-1 hash of namespace + name |
| v6 | Reordered time | Same as v1 but with time fields reordered for sortability |
| v7 | Unix epoch time | Millisecond precision, monotonic counter |
| v8 | Custom | Vendor-specific, custom bytes |
| Nil | Special | All zeros |
| Max | Special | All 0xFF |

## Type System

```c
typedef struct {
    uint8_t bytes[16];  // 128-bit UUID
} uuid_t;
```

UUIDs are value types. They can be passed by value for small copies, or by pointer for API calls.
