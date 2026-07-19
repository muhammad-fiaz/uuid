---
title: Examples
description: Working examples demonstrating all uuid library features.
---

# Examples

Working examples demonstrating all uuid library features.

## Available Examples

| Example | Description | Source |
|---------|-------------|--------|
| [Basic](./basic.md) | Generate, parse, format, and inspect UUIDs | [`basic.c`](https://github.com/muhammad-fiaz/uuid/blob/main/examples/basic.c) |
| [UUID v1](./v1.md) | Time-based UUID generation with metadata extraction | [`v1.c`](https://github.com/muhammad-fiaz/uuid/blob/main/examples/v1.c) |
| [UUID v3](./v3.md) | MD5 name-based deterministic UUID generation | [`v3.c`](https://github.com/muhammad-fiaz/uuid/blob/main/examples/v3.c) |
| [UUID v4](./v4.md) | Cryptographically secure random UUID generation | [`v4.c`](https://github.com/muhammad-fiaz/uuid/blob/main/examples/v4.c) |
| [UUID v5](./v5.md) | SHA-1 name-based deterministic UUID generation | [`v5.c`](https://github.com/muhammad-fiaz/uuid/blob/main/examples/v5.c) |
| [UUID v6](./v6.md) | Reordered time-based UUID generation | [`v6.c`](https://github.com/muhammad-fiaz/uuid/blob/main/examples/v6.c) |
| [UUID v7](./v7.md) | Unix epoch time-based monotonic UUID generation | [`v7.c`](https://github.com/muhammad-fiaz/uuid/blob/main/examples/v7.c) |
| [UUID v8](./v8.md) | Custom UUID generation with full control | [`v8.c`](https://github.com/muhammad-fiaz/uuid/blob/main/examples/v8.c) |
| [Parsing](./parsing.md) | Parse UUIDs from various string formats | [`parsing.c`](https://github.com/muhammad-fiaz/uuid/blob/main/examples/parsing.c) |
| [Formatting](./formatting.md) | Format UUIDs to canonical, compact, braces, and binary | [`formatting.c`](https://github.com/muhammad-fiaz/uuid/blob/main/examples/formatting.c) |
| [Validation](./validation.md) | Validate UUID strings in multiple formats | [`validation.c`](https://github.com/muhammad-fiaz/uuid/blob/main/examples/validation.c) |
| [Comparison](./comparison.md) | Compare and sort UUIDs ascending/descending | [`comparison.c`](https://github.com/muhammad-fiaz/uuid/blob/main/examples/comparison.c) |
| [Serialization](./serialization.md) | Binary serialization and deserialization | [`serialization.c`](https://github.com/muhammad-fiaz/uuid/blob/main/examples/serialization.c) |
| [Threading](./threading.md) | Thread-safe UUID generation with multiple threads | [`threading.c`](https://github.com/muhammad-fiaz/uuid/blob/main/examples/threading.c) |
| [Error Handling](./error-handling.md) | Error codes, messages, and edge cases | [`error_handling.c`](https://github.com/muhammad-fiaz/uuid/blob/main/examples/error_handling.c) |
| [Custom UUID](./custom-uuid.md) | Create UUIDs from explicit bytes and custom data | [`custom_uuid.c`](https://github.com/muhammad-fiaz/uuid/blob/main/examples/custom_uuid.c) |
| [Binary Conversion](./binary-conversion.md) | Binary serialization, deserialization, and byte access | [`binary_conversion.c`](https://github.com/muhammad-fiaz/uuid/blob/main/examples/binary_conversion.c) |

## Running Examples

```bash
cmake -B build -DUUID_BUILD_EXAMPLES=ON -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release

# Run any example
./build/examples/example_basic
./build/examples/example_v4
./build/examples/example_v7
```
