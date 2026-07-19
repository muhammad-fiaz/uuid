# Advanced Usage

Advanced features and patterns for the uuid library.

## Custom UUID v8

Create vendor-specific UUIDs:

```c
#include <uuid/uuid.h>

// Custom 12 bytes (version/variant set automatically)
uint8_t custom[12] = {0xDE, 0xAD, 0xBE, 0xEF, 0xCA, 0xFE, 0xBA, 0xBE,
                       0x01, 0x23, 0x45, 0x67};
uuid_t uuid;
uuid_v8(&uuid, custom);

// Fully custom (no auto version/variant)
uint8_t full[16] = {0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF9, 0xF8,
                     0xF7, 0xF6, 0xF5, 0xF4, 0xF3, 0xF2, 0xF1, 0xF0};
uuid_v8_custom(&uuid, full);
```

## Custom Namespace UUIDs

```c
#include <uuid/uuid.h>

// Create your own namespace UUID
uuid_t custom_ns;
uuid_v4(&custom_ns);

// Use it with v3 or v5
uuid_t uuid;
uuid_v5(&custom_ns, "my-app-entity-123", 17, &uuid);
```

## Batch Generation

```c
#include <uuid/uuid.h>

uuid_t uuids[1000];
uuid_v7_state_t state;
uuid_v7_init(&state);

for (int i = 0; i < 1000; i++) {
    uuid_v7(&state, &uuids[i]);
}
```

## Binary Serialization

```c
#include <uuid/uuid.h>

uuid_t uuid;
uuid_v4(&uuid);

// Serialize to bytes
uint8_t buf[16];
uuid_serialize(&uuid, buf, sizeof(buf));

// Deserialize from bytes
uuid_t restored;
uuid_deserialize(&restored, buf, sizeof(buf));
```

## Using as Hash Table Key

```c
#include <uuid/uuid.h>

// FNV-1a hash for hash tables
uuid_t key;
uuid_v4(&key);
uint64_t hash = uuid_hash(&key);
```

## Sorting UUID Arrays

```c
#include <uuid/uuid.h>

uuid_t uuids[100];
for (int i = 0; i < 100; i++) uuid_v7(&state, &uuids[i]);

// Sort ascending (newest first)
uuid_sort_asc(uuids, 100);

// Sort descending (newest first)
uuid_sort_desc(uuids, 100);
```
