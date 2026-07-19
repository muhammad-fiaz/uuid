# Formatting

Functions for formatting UUIDs as strings.

## uuid_format

```c
uuid_error_t uuid_format(const uuid_t *uuid, char *buf, size_t size);
```

Format a UUID as a canonical string: `xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx\0`

**Parameters:**
- `uuid`: UUID to format
- `buf`: Output buffer (must be at least 37 bytes)
- `size`: Size of buffer

**Returns:** `UUID_OK` on success, `UUID_E_BUFFER_TOO_SMALL` if too small

```c
uuid_t uuid;
char buf[UUID_STRING_LEN]; // 37 bytes
uuid_v4(&uuid);
uuid_format(&uuid, buf, sizeof(buf));
// buf = "550e8400-e29b-41d4-a716-446655440000"
```

## uuid_format_compact

```c
uuid_error_t uuid_format_compact(const uuid_t *uuid, char *buf, size_t size);
```

Format without hyphens: `xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\0`

## uuid_format_braces

```c
uuid_error_t uuid_format_braces(const uuid_t *uuid, char *buf, size_t size);
```

Format with braces: `{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}\0`

## uuid_format_options

```c
uuid_error_t uuid_format_options(const uuid_t *uuid, char *buf, size_t size,
                                 int format);
```

Format with custom options (bitmask).

**Options:**
- `UUID_FMT_COMPACT` - No hyphens
- `UUID_FMT_BRACES` - Wrap in braces
- `UUID_FMT_UPPER` - Uppercase hex
- `UUID_FMT_BINARY` - Raw 16 bytes

## uuid_format_binary

```c
uuid_error_t uuid_format_binary(const uuid_t *uuid, void *buf, size_t size);
```

Format as raw 16-byte binary.

## uuid_to_string

```c
char *uuid_to_string(const uuid_t *uuid, char *buf, size_t size);
```

Convenience wrapper. Returns `buf` on success, `NULL` on failure.
