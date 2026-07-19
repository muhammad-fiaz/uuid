# Generation

Functions for generating UUIDs.

## uuid_v4

```c
uuid_error_t uuid_v4(uuid_t *uuid);
```

Generate a random UUID v4 using cryptographically secure random.

**Parameters:**
- `uuid`: Pointer to store generated UUID

**Returns:** `UUID_OK` on success, `UUID_E_RANDOM` if random generation fails

```c
uuid_t uuid;
uuid_v4(&uuid);
```

## uuid_v1

```c
uuid_error_t uuid_v1(uuid_v1_state_t *state, uuid_t *uuid);
```

Generate a UUID v1 from explicit state.

## uuid_v1_init

```c
uuid_error_t uuid_v1_init(uuid_v1_state_t *state);
```

Initialize UUID v1 state with random clock sequence and node.

## uuid_v1_generate

```c
uuid_error_t uuid_v1_generate(uuid_t *uuid);
```

Generate UUID v1 using thread-local state.

## uuid_v3

```c
uuid_error_t uuid_v3(const uuid_t *namespace_uuid, const void *name,
                     size_t name_len, uuid_t *uuid);
```

Generate UUID v3 (MD5 name-based).

## uuid_v3_ns

```c
uuid_error_t uuid_v3_ns(uuid_namespace_t ns, const char *name,
                        size_t name_len, uuid_t *uuid);
```

Generate UUID v3 with a well-known namespace.

## uuid_v5

```c
uuid_error_t uuid_v5(const uuid_t *namespace_uuid, const void *name,
                     size_t name_len, uuid_t *uuid);
```

Generate UUID v5 (SHA-1 name-based).

## uuid_v5_ns

```c
uuid_error_t uuid_v5_ns(uuid_namespace_t ns, const char *name,
                        size_t name_len, uuid_t *uuid);
```

Generate UUID v5 with a well-known namespace.

## uuid_v6

```c
uuid_error_t uuid_v6(uuid_v1_state_t *state, uuid_t *uuid);
```

Generate UUID v6 (reordered time-based).

## uuid_v7

```c
uuid_error_t uuid_v7(uuid_v7_state_t *state, uuid_t *uuid);
```

Generate UUID v7 (Unix epoch, monotonic).

## uuid_v7_init

```c
uuid_error_t uuid_v7_init(uuid_v7_state_t *state);
```

Initialize UUID v7 state.

## uuid_v7_generate

```c
uuid_error_t uuid_v7_generate(uuid_t *uuid);
```

Generate UUID v7 using thread-local state.

## uuid_v8

```c
uuid_error_t uuid_v8(uuid_t *uuid, const uint8_t custom[12]);
```

Generate UUID v8 from custom bytes (version/variant auto-set).

## uuid_v8_custom

```c
uuid_error_t uuid_v8_custom(uuid_t *uuid, const uint8_t custom[16]);
```

Generate fully custom UUID v8.

## uuid_nil / uuid_max

```c
uuid_error_t uuid_nil(uuid_t *uuid);
uuid_error_t uuid_max(uuid_t *uuid);
```

Convenience functions for nil/max UUIDs.
