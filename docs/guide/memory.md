# Memory Model

The uuid library has a simple, predictable memory model.

## Key Principles

1. **No Hidden Allocations**: Core API functions never allocate memory
2. **Caller-Provided Buffers**: All output buffers are provided by the caller
3. **No Global Mutable State**: Thread-safe by design
4. **Value Types**: UUIDs are 16-byte structs, pass by value or pointer

## UUID Structure

```c
typedef struct {
    uint8_t bytes[16];
} uuid_t;
```

Size: 16 bytes. Alignment: 1 byte.

## Stack Allocation

```c
// UUIDs live on the stack
uuid_t uuid;  // 16 bytes on stack
char buf[UUID_STRING_LEN];  // 37 bytes on stack

uuid_v4(&uuid);
uuid_format(&uuid, buf, sizeof(buf));
```

## Array of UUIDs

```c
// Array of 1000 UUIDs = 16 KB on stack (or heap)
uuid_t uuids[1000];

for (int i = 0; i < 1000; i++) {
    uuid_v4(&uuids[i]);
}

uuid_sort_asc(uuids, 1000);
```

## Naming-based UUIDs (v3, v5)

Name-based UUIDs (v3 and v5) require a temporary buffer for the namespace + name concatenation. This buffer is allocated with `malloc` and freed before returning.

```c
// Internally: malloc(UUID_SIZE + name_len), hash, free
uuid_v5_ns(UUID_NS_DNS, "example.com", 11, &uuid);
```

This is the only path that allocates memory. For embedded systems with no malloc, implement a custom allocator or use other UUID versions.

## State Objects

State objects for v1/v6/v7 are small, fixed-size structs:

```c
typedef struct {
    uint64_t timestamp;    // 8 bytes
    uint16_t clock_seq;    // 2 bytes
    uint8_t  node[6];      // 6 bytes
    int      initialized;  // 4 bytes
} uuid_v1_state_t;         // ~20 bytes
```
