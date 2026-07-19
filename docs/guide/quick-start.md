# Quick Start

Get up and running with uuid in minutes.

## Generate Your First UUID

```c
#include <uuid/uuid.h>
#include <stdio.h>

int main(void) {
    uuid_t uuid;
    char buf[UUID_STRING_LEN];

    // Random UUID v4
    uuid_v4(&uuid);
    uuid_format(&uuid, buf, sizeof(buf));
    printf("Generated: %s\n", buf);

    return 0;
}
```

## Parse a UUID

```c
#include <uuid/uuid.h>
#include <stdio.h>

int main(void) {
    uuid_t uuid;
    char buf[UUID_STRING_LEN];

    if (uuid_parse(&uuid, "550e8400-e29b-41d4-a716-446655440000") == UUID_OK) {
        printf("Version: %d\n", uuid_version(&uuid));
        printf("Variant: %d\n", uuid_variant(&uuid));
    }

    return 0;
}
```

## Use Well-Known Namespaces

```c
#include <uuid/uuid.h>
#include <stdio.h>

int main(void) {
    uuid_t uuid;
    char buf[UUID_STRING_LEN];

    // UUID v5 (SHA-1) with DNS namespace
    uuid_v5_ns(UUID_NS_DNS, "example.com", 11, &uuid);
    uuid_format(&uuid, buf, sizeof(buf));
    printf("v5(DNS, example.com): %s\n", buf);

    return 0;
}
```

## Generate Sortable UUIDs

```c
#include <uuid/uuid.h>
#include <stdio.h>

int main(void) {
    uuid_v7_state_t state;
    uuid_t uuid;
    char buf[UUID_STRING_LEN];

    uuid_v7_init(&state);

    // Generate 5 sortable UUIDs
    for (int i = 0; i < 5; i++) {
        uuid_v7(&state, &uuid);
        uuid_format(&uuid, buf, sizeof(buf));
        printf("  %s\n", buf);
    }

    return 0;
}
```

## Error Handling

```c
#include <uuid/uuid.h>
#include <stdio.h>

int main(void) {
    uuid_t uuid;
    uuid_error_t err;

    err = uuid_parse(&uuid, "not-a-uuid");
    if (err != UUID_OK) {
        printf("Error: %s\n", uuid_strerror(err));
    }

    return 0;
}
```

## Build and Run

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
./build/examples/Release/example_basic
```
