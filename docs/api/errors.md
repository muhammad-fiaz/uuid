# Errors

Error handling in the uuid library.

## Error Codes

```c
typedef enum {
    UUID_OK                 =  0,  // Success
    UUID_E_INVALID_ARG      = -1,  // Invalid argument
    UUID_E_INVALID_UUID     = -2,  // Invalid UUID value
    UUID_E_INVALID_FORMAT   = -3,  // Invalid string format
    UUID_E_INVALID_LENGTH   = -4,  // Invalid input length
    UUID_E_INVALID_VERSION  = -5,  // Invalid UUID version
    UUID_E_INVALID_VARIANT  = -6,  // Invalid UUID variant
    UUID_E_BUFFER_TOO_SMALL = -7,  // Buffer too small
    UUID_E_NO_MEMORY        = -8,  // Memory allocation failed
    UUID_E_NOT_SUPPORTED    = -9,  // Operation not supported
    UUID_E_PLATFORM         = -10, // Platform error
    UUID_E_RANDOM           = -11, // Random generation failed
    UUID_E_OVERFLOW         = -12, // Counter overflow
    UUID_E_NAMESPACE        = -13, // Invalid namespace
    UUID_E_TIMEOUT          = -14  // Operation timed out
} uuid_error_t;
```

## uuid_strerror

```c
const char *uuid_strerror(uuid_error_t error);
```

Get human-readable error message for an error code.

```c
uuid_t uuid;
uuid_error_t err = uuid_parse(&uuid, "invalid");
if (err != UUID_OK) {
    printf("Error: %s\n", uuid_strerror(err));
    // "Error: Invalid string format"
}
```

## uuid_last_error

```c
const char *uuid_last_error(void);
```

Get the last error message (thread-local).

```c
uuid_init_nil(NULL); // Fails
printf("Last error: %s\n", uuid_last_error());
// "Last error: NULL pointer"
```

## Error Pattern

```c
uuid_t uuid;
uuid_error_t err;

err = uuid_parse(&uuid, "550e8400-e29b-41d4-a716-446655440000");
if (err != UUID_OK) {
    fprintf(stderr, "Parse failed: %s\n", uuid_strerror(err));
    return 1;
}

// uuid is now valid
```
