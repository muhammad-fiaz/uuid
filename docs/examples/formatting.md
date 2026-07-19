---
title: Formatting Example
description: Format UUIDs into canonical, compact, braced, uppercase, and binary representations.
---

# Formatting Example

Demonstrates all formatting options.

## Source Code

```c
/*
 * formatting.c - UUID formatting examples
 * Copyright (c) 2026 Muhammad Fiaz - MIT License
 */

#include <uuid/uuid.h>
#include <stdio.h>

int main(void) {
    uuid_t uuid;
    char buf[64];

    printf("uuid v%s - Formatting Example\n\n", uuid_version_string());

    uuid_parse(&uuid, "550e8400-e29b-41d4-a716-446655440000");

    uuid_format(&uuid, buf, sizeof(buf));
    printf("Canonical:   %s\n", buf);

    uuid_format_compact(&uuid, buf, sizeof(buf));
    printf("Compact:     %s\n", buf);

    uuid_format_braces(&uuid, buf, sizeof(buf));
    printf("Braces:      %s\n", buf);

    uuid_format_options(&uuid, buf, sizeof(buf), UUID_FMT_UPPER);
    printf("Uppercase:   %s\n", buf);

    uuid_format_options(&uuid, buf, sizeof(buf), UUID_FMT_COMPACT | UUID_FMT_UPPER);
    printf("Compact+UP:  %s\n", buf);

    uint8_t bin[16];
    uuid_format_binary(&uuid, bin, sizeof(bin));
    printf("Binary:      %02x %02x %02x %02x ... %02x %02x\n",
           bin[0], bin[1], bin[2], bin[3], bin[14], bin[15]);

    return 0;
}
```

## Output

```
uuid v0.1.0 - Formatting Example

Canonical:   550e8400-e29b-41d4-a716-446655440000
Compact:     550e8400e29b41d4a716446655440000
Braces:      {550e8400-e29b-41d4-a716-446655440000}
Uppercase:   550E8400-E29B-41D4-A716-446655440000
Compact+UP:  550E8400E29B41D4A716446655440000
Binary:      55 0e 84 00 ... 00 00
```
