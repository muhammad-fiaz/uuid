# Thread Safety

The uuid library is designed for concurrent use.

## Thread Safety Model

All public API functions are thread-safe unless explicitly documented otherwise.

### Thread-Local State

UUID v1, v6, and v7 generation uses thread-local state for convenience functions:

```c
// Thread-safe: each thread has its own state
uuid_t uuid;
uuid_v4(&uuid);  // Uses thread-local random
```

### Explicit State

For maximum control, use explicit state objects:

```c
// Each thread creates its own state
uuid_v7_state_t my_state;
uuid_v7_init(&my_state);

// Use only from this thread
uuid_v7(&my_state, &uuid);
```

## What is Thread-Safe

- All generation functions (`uuid_v4`, `uuid_v1`, `uuid_v7`, etc.)
- All parsing functions
- All formatting functions
- All validation functions
- All comparison functions
- All hashing functions
- All serialization functions
- Error message functions (thread-local)

## What Requires Synchronization

- Sharing a `uuid_v1_state_t` or `uuid_v7_state_t` between threads
  (use one state per thread, or protect with a mutex)

## Example: Multi-threaded Generation

```c
#include <uuid/uuid.h>
#include <stdio.h>
#include <pthread.h>

void *generate_uuids(void *arg) {
    int id = *(int *)arg;
    uuid_t uuid;
    char buf[UUID_STRING_LEN];

    for (int i = 0; i < 1000; i++) {
        uuid_v4(&uuid);
        uuid_format(&uuid, buf, sizeof(buf));
        // Thread-local format buffer is safe
    }
    return NULL;
}
```
