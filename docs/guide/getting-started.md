# Getting Started

A quick introduction to using the uuid library.

## Overview

`uuid` is a production-grade UUID library for C and C++ that implements all UUID versions defined by [RFC 9562](https://www.rfc-editor.org/rfc/rfc9562). It has zero third-party runtime dependencies and supports C99 through C23.

## Basic Usage

### Generate a UUID

```c
#include <uuid/uuid.h>
#include <stdio.h>

int main(void) {
    uuid_t uuid;
    char buf[UUID_STRING_LEN];

    // Generate a random UUID v4
    uuid_v4(&uuid);
    uuid_format(&uuid, buf, sizeof(buf));
    printf("UUID: %s\n", buf);

    return 0;
}
```

### Parse and Validate

```c
#include <uuid/uuid.h>
#include <stdio.h>

int main(void) {
    uuid_t uuid;
    char buf[UUID_STRING_LEN];

    // Parse a UUID string
    if (uuid_parse(&uuid, "550e8400-e29b-41d4-a716-446655440000") == UUID_OK) {
        uuid_format(&uuid, buf, sizeof(buf));
        printf("Parsed: %s\n", buf);
        printf("Version: %d\n", uuid_version(&uuid));
    }

    // Validate without parsing
    if (uuid_validate("550e8400-e29b-41d4-a716-446655440000") == UUID_OK) {
        printf("Valid UUID\n");
    }

    return 0;
}
```

### Time-based UUIDs

```c
#include <uuid/uuid.h>
#include <stdio.h>

int main(void) {
    uuid_v7_state_t state;
    uuid_t uuid;
    char buf[UUID_STRING_LEN];

    // Generate sortable UUID v7
    uuid_v7_init(&state);
    uuid_v7(&state, &uuid);
    uuid_format(&uuid, buf, sizeof(buf));
    printf("UUID v7: %s\n", buf);

    return 0;
}
```

## Next Steps

- [Installation](/guide/installation) - How to install and integrate uuid
- [Quick Start](/guide/quick-start) - Detailed quick start guide
- [UUID Versions](/uuid/overview) - Learn about all supported UUID versions
- [API Reference](/api/overview) - Complete API documentation
