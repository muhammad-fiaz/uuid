# Initialization

Functions for initializing UUIDs.

## uuid_init_nil

```c
uuid_error_t uuid_init_nil(uuid_t *uuid);
```

Initialize a nil UUID (all zeros).

**Parameters:**
- `uuid`: Pointer to UUID to initialize

**Returns:** `UUID_OK` on success

```c
uuid_t uuid;
uuid_init_nil(&uuid);
// uuid.bytes = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
```

## uuid_init_max

```c
uuid_error_t uuid_init_max(uuid_t *uuid);
```

Initialize a max UUID (all 0xFF).

## uuid_init_from_bytes

```c
uuid_error_t uuid_init_from_bytes(uuid_t *uuid, const uint8_t data[16]);
```

Initialize a UUID from a 16-byte array.

## uuid_copy

```c
uuid_error_t uuid_copy(uuid_t *dst, const uuid_t *src);
```

Copy a UUID.

## uuid_set

```c
uuid_error_t uuid_set(uuid_t *uuid, uint8_t value);
```

Set all bytes of a UUID to a specific value.

## Constants

```c
static const uuid_t UUID_NIL = {{0}};           // Nil UUID
static const uuid_t UUID_MAX_UUID = {{0xFF...}}; // Max UUID
```

These can be used directly without calling init functions.
