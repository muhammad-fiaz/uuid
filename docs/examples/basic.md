---
title: Basic Usage
description: Generate, parse, format, and inspect UUIDs.
---

# Basic Usage

Generate, parse, format, and inspect UUIDs.

## Source Code

```c
/*
 * basic.c - Basic UUID usage example
 * Copyright (c) 2026 Muhammad Fiaz - MIT License
 */

#include <uuid/uuid.h>
#include <stdio.h>

int main(void) {
    uuid_t uuid;
    char buf[UUID_STRING_LEN];

    printf("uuid v%s - Basic Example\n\n", uuid_version_string());

    /* Generate a random UUID v4 */
    uuid_v4(&uuid);
    uuid_format(&uuid, buf, sizeof(buf));
    printf("Generated UUID:  %s\n", buf);

    /* Parse a UUID */
    uuid_parse(&uuid, "550e8400-e29b-41d4-a716-446655440000");
    uuid_format(&uuid, buf, sizeof(buf));
    printf("Parsed UUID:     %s\n", buf);

    /* Check version and variant */
    printf("Version:         %d\n", uuid_version(&uuid));
    printf("Variant:         %d\n", uuid_variant(&uuid));

    /* Check if nil */
    printf("Is nil:          %s\n", uuid_is_nil(&uuid) ? "yes" : "no");

    /* Hash */
    printf("Hash:            0x%016llx\n", (unsigned long long)uuid_hash(&uuid));

    return 0;
}
```

## Output

```
uuid v0.1.0 - Basic Example

Generated UUID:  394599f8-b268-4802-9584-766cbb90a219
Parsed UUID:     550e8400-e29b-41d4-a716-446655440000
Version:         4
Variant:         1
Is nil:          no
Hash:            0x07ae121fff2ab1b2
```
