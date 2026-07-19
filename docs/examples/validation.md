---
title: Validation Example
description: Demonstrates input validation for UUID strings in various formats.
---

# Validation Example

This example demonstrates how to validate UUID strings in various formats, including canonical, uppercase, compact, braced, nil, max, and invalid strings.

## Source Code

```c
/*
 * validation.c - UUID validation examples
 * Copyright (c) 2026 Muhammad Fiaz - MIT License
 */

#include <uuid/uuid.h>
#include <stdio.h>

int main(void) {
    int i;
    struct { const char *str; const char *desc; } tests[] = {
        {"550e8400-e29b-41d4-a716-446655440000", "canonical v4"},
        {"550E8400-E29B-41D4-A716-446655440000", "uppercase"},
        {"550e8400e29b41d4a716446655440000",      "compact"},
        {"{550e8400-e29b-41d4-a716-446655440000}","braces"},
        {"00000000-0000-0000-0000-000000000000",  "nil"},
        {"ffffffff-ffff-ffff-ffff-ffffffffffff",  "max"},
        {"not-a-uuid",                            "invalid string"},
        {"550e8400-e29b-41d4-a716",               "too short"},
        {"550e8400-e29b-41d4-a716-446655440000-extra","too long"},
        {"gggggggg-gggg-gggg-gggg-gggggggggggg",  "invalid hex"},
    };

    printf("uuid v%s - Validation Example\n\n", uuid_version_string());

    for (i = 0; i < 10; i++) {
        uuid_error_t err = uuid_validate(tests[i].str);
        printf("  %-15s: %s\n", tests[i].desc, err == UUID_OK ? "VALID" : uuid_strerror(err));
    }

    return 0;
}
```

## Output

```
uuid v0.1.0 - Validation Example

  canonical v4   : VALID
  uppercase      : VALID
  compact        : VALID
  braces         : VALID
  nil            : VALID
  max            : VALID
  invalid string : Invalid string format
  too short      : Invalid string format
  too long       : Invalid string format
  invalid hex    : Invalid string format
```