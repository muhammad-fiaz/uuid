# Parsing

Functions for parsing UUID strings.

## uuid_parse

```c
uuid_error_t uuid_parse(uuid_t *uuid, const char *str);
```

Parse a UUID from a null-terminated string.

**Accepted Formats:**
- `550e8400-e29b-41d4-a716-446655440000` (canonical)
- `550E8400-E29B-41D4-A716-446655440000` (uppercase)
- `550e8400e29b41d4a716446655440000` (compact)
- `{550e8400-e29b-41d4-a716-446655440000}` (braces)

**Parameters:**
- `uuid`: Pointer to store parsed UUID
- `str`: Null-terminated string to parse

**Returns:** `UUID_OK` on success, error code on failure

```c
uuid_t uuid;
if (uuid_parse(&uuid, "550e8400-e29b-41d4-a716-446655440000") == UUID_OK) {
    // Success
}
```

## uuid_parse_n

```c
uuid_error_t uuid_parse_n(uuid_t *uuid, const char *str, size_t len);
```

Parse a UUID from a string with length limit.

## uuid_parse_binary

```c
uuid_error_t uuid_parse_binary(uuid_t *uuid, const void *data, size_t len);
```

Parse a UUID from a 16-byte binary buffer.

## uuid_validate

```c
uuid_error_t uuid_validate(const char *str);
```

Validate a UUID string without storing the result.

```c
if (uuid_validate("550e8400-e29b-41d4-a716-446655440000") == UUID_OK) {
    printf("Valid UUID\n");
}
```

## uuid_validate_n

```c
uuid_error_t uuid_validate_n(const char *str, size_t len);
```

Validate with length limit.

## Error Codes

| Code | Meaning |
|------|---------|
| `UUID_OK` | Valid UUID |
| `UUID_E_INVALID_FORMAT` | Invalid format or characters |
| `UUID_E_INVALID_LENGTH` | Wrong length |
| `UUID_E_INVALID_ARG` | NULL pointer |
