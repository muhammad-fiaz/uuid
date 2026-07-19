# API Overview

Complete API reference for the uuid library.

## Header

```c
#include <uuid/uuid.h>
```

## Types

| Type | Description |
|------|-------------|
| `uuid_t` | UUID structure (16 bytes) |
| `uuid_error_t` | Error code enum |
| `uuid_version_t` | UUID version enum |
| `uuid_variant_t` | UUID variant enum |
| `uuid_namespace_t` | Well-known namespace enum |
| `uuid_format_t` | Formatting options enum |
| `uuid_v1_state_t` | State for UUID v1/v6 generation |
| `uuid_v7_state_t` | State for UUID v7 generation |

## Constants

| Constant | Value | Description |
|----------|-------|-------------|
| `UUID_STRING_LEN` | 37 | Canonical string length (with null) |
| `UUID_COMPACT_LEN` | 33 | Compact string length (with null) |
| `UUID_SIZE` | 16 | UUID size in bytes |
| `UUID_NIL` | `{0}` | Nil UUID constant |
| `UUID_MAX_UUID` | `{0xFF...}` | Max UUID constant |

## Functions

### Initialization
- `uuid_init_nil()` - Initialize nil UUID
- `uuid_init_max()` - Initialize max UUID
- `uuid_init_from_bytes()` - Initialize from bytes
- `uuid_copy()` - Copy UUID
- `uuid_set()` - Set all bytes

### Generation
- `uuid_v1()` - Generate UUID v1
- `uuid_v1_init()` - Initialize v1 state
- `uuid_v3()` - Generate UUID v3
- `uuid_v3_ns()` - Generate UUID v3 with namespace enum
- `uuid_v4()` - Generate UUID v4
- `uuid_v5()` - Generate UUID v5
- `uuid_v5_ns()` - Generate UUID v5 with namespace enum
- `uuid_v6()` - Generate UUID v6
- `uuid_v6_init()` - Initialize v6 state
- `uuid_v7()` - Generate UUID v7
- `uuid_v7_init()` - Initialize v7 state
- `uuid_v7_generate()` - Generate v7 with thread-local state
- `uuid_v8()` - Generate UUID v8
- `uuid_v8_custom()` - Generate fully custom UUID v8
- `uuid_nil()` - Generate nil UUID
- `uuid_max()` - Generate max UUID

### Parsing
- `uuid_parse()` - Parse from string
- `uuid_parse_n()` - Parse from string with length
- `uuid_parse_binary()` - Parse from binary
- `uuid_validate()` - Validate string
- `uuid_validate_n()` - Validate string with length

### Formatting
- `uuid_format()` - Format as canonical string
- `uuid_format_compact()` - Format as compact string
- `uuid_format_braces()` - Format with braces
- `uuid_format_options()` - Format with options
- `uuid_format_binary()` - Format as binary
- `uuid_to_string()` - Format to buffer (returns pointer)

### Inspection
- `uuid_version()` - Get version number
- `uuid_variant()` - Get variant
- `uuid_get_version()` - Get version as enum
- `uuid_get_variant()` - Get variant as enum
- `uuid_v1_timestamp()` - Extract v1 timestamp
- `uuid_v7_timestamp_ms()` - Extract v7 timestamp
- `uuid_v1_clock_seq()` - Extract v1 clock sequence
- `uuid_v1_node()` - Extract v1 node

### Comparison
- `uuid_compare()` - Compare two UUIDs
- `uuid_compare_asc()` - qsort ascending comparator
- `uuid_compare_desc()` - qsort descending comparator

### Sorting
- `uuid_sort_asc()` - Sort array ascending
- `uuid_sort_desc()` - Sort array descending

### Hashing
- `uuid_hash()` - FNV-1a hash
- `uuid_md5()` - MD5 hash
- `uuid_sha1()` - SHA-1 hash

### Serialization
- `uuid_serialize()` - Serialize to bytes
- `uuid_deserialize()` - Deserialize from bytes

### Utilities
- `uuid_is_nil()` - Check if nil
- `uuid_is_max()` - Check if max
- `uuid_swap()` - Swap two UUIDs
- `uuid_byte_at()` - Get specific byte
- `uuid_bytes()` - Get raw byte pointer
- `uuid_strerror()` - Get error message
- `uuid_last_error()` - Get last error
- `uuid_version_string()` - Get version string
- `uuid_version_info()` - Get version info
- `uuid_namespace()` - Get namespace UUID
- `uuid_get_namespace()` - Get namespace UUID (alias)
