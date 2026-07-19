# Validation

Functions for validating UUID strings.

## uuid_validate

```c
uuid_error_t uuid_validate(const char *str);
```

Validate a UUID string. Returns `UUID_OK` if valid, error code otherwise.

```c
if (uuid_validate("550e8400-e29b-41d4-a716-446655440000") == UUID_OK) {
    printf("Valid UUID\n");
}
```

## uuid_validate_n

```c
uuid_error_t uuid_validate_n(const char *str, size_t len);
```

Validate with explicit length.

## Accepted Formats

- Canonical: `xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx`
- Compact: `xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx`
- Braces: `{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}`
- Mixed case
- Leading/trailing whitespace (in relaxed mode)

## Error Codes

| Code | Meaning |
|------|---------|
| `UUID_OK` | Valid UUID |
| `UUID_E_INVALID_FORMAT` | Invalid characters or format |
| `UUID_E_INVALID_LENGTH` | Wrong length |
| `UUID_E_INVALID_ARG` | NULL pointer |
