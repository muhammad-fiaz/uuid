---
title: Error Handling Example
description: Demonstrates error handling with various invalid operations.
---

# Error Handling Example

This example demonstrates how to handle errors when performing various invalid operations on UUIDs.

## Source Code

```c
/*
 * error_handling.c - Error handling example
 * Copyright (c) 2026 Muhammad Fiaz - MIT License
 */

#include <uuid/uuid.h>
#include <stdio.h>

int main(void) {
    uuid_t uuid;
    uuid_error_t err;

    printf("uuid v%s - Error Handling Example\n\n", uuid_version_string());

    /* Invalid parse */
    err = uuid_parse(&uuid, "not-a-uuid");
    printf("Parse invalid:  %s -> %s\n", "not-a-uuid", uuid_strerror(err));

    /* NULL pointer */
    err = uuid_init_nil(NULL);
    printf("Init nil NULL:  %s\n", uuid_strerror(err));

    /* Buffer too small */
    char small_buf[5];
    uuid_v4(&uuid);
    err = uuid_format(&uuid, small_buf, sizeof(small_buf));
    printf("Buffer small:   %s\n", uuid_strerror(err));

    /* Invalid namespace */
    err = uuid_namespace((uuid_namespace_t)99, &uuid);
    printf("Invalid ns:     %s\n", uuid_strerror(err));

    /* Last error */
    printf("\nLast error msg: %s\n", uuid_last_error());

    return 0;
}
```

## Output

```
uuid v0.1.0 - Error Handling Example

Parse invalid:  not-a-uuid -> Invalid string format
Init nil NULL:  Invalid argument
Buffer small:   Buffer too small
Invalid ns:     Invalid namespace

Last error msg: Invalid namespace enum
```