---
title: Serialization Example
description: Demonstrates binary serialization and deserialization of UUIDs.
---

# Serialization Example

This example demonstrates how to serialize a UUID to binary format and deserialize it back to verify data integrity.

## Source Code

```c
/*
 * serialization.c - UUID serialization/deserialization example
 * Copyright (c) 2026 Muhammad Fiaz - MIT License
 */

#include <uuid/uuid.h>
#include <stdio.h>

int main(void) {
    uuid_t a, b;
    uint8_t buf[UUID_SIZE];
    char str[UUID_STRING_LEN];
    int i;

    printf("uuid v%s - Serialization Example\n\n", uuid_version_string());

    /* Generate and serialize */
    uuid_v4(&a);
    uuid_format(&a, str, sizeof(str));
    printf("Original:        %s\n", str);

    uuid_serialize(&a, buf, sizeof(buf));
    printf("Serialized:      ");
    for (i = 0; i < UUID_SIZE; i++) printf("%02x ", buf[i]);
    printf("\n");

    /* Deserialize */
    uuid_deserialize(&b, buf, sizeof(buf));
    uuid_format(&b, str, sizeof(str));
    printf("Deserialized:    %s\n", str);

    printf("Match:           %s\n",
           uuid_compare(&a, &b) == 0 ? "yes" : "no");

    return 0;
}
```

## Output

```
uuid v0.1.0 - Serialization Example

Original:        c68a987a-bb57-4690-965e-b48b947cf90c
Serialized:      c6 8a 98 7a bb 57 46 90 96 5e b4 8b 94 7c f9 0c 
Deserialized:    c68a987a-bb57-4690-965e-b48b947cf90c
Match:           yes
```