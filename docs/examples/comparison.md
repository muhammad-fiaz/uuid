---
title: Comparison & Sorting Example
description: Demonstrates UUID comparison and sorting operations.
---

# Comparison & Sorting Example

This example demonstrates how to compare UUIDs and sort them in ascending and descending order.

## Source Code

```c
/*
 * comparison.c - UUID comparison and sorting examples
 * Copyright (c) 2026 Muhammad Fiaz - MIT License
 */

#include <uuid/uuid.h>
#include <stdio.h>

int main(void) {
    uuid_t uuids[5];
    char buf[UUID_STRING_LEN];
    int i;

    printf("uuid v%s - Comparison & Sorting Example\n\n", uuid_version_string());

    /* Create some UUIDs */
    uuid_init_nil(&uuids[0]);
    uuid_v4(&uuids[1]);
    uuid_v4(&uuids[2]);
    uuid_v4(&uuids[3]);
    uuid_init_max(&uuids[4]);

    printf("Before sorting:\n");
    for (i = 0; i < 5; i++) {
        uuid_format(&uuids[i], buf, sizeof(buf));
        printf("  [%d] %s\n", i, buf);
    }

    /* Sort ascending */
    uuid_sort_asc(uuids, 5);
    printf("\nAfter ascending sort:\n");
    for (i = 0; i < 5; i++) {
        uuid_format(&uuids[i], buf, sizeof(buf));
        printf("  [%d] %s\n", i, buf);
    }

    /* Sort descending */
    uuid_sort_desc(uuids, 5);
    printf("\nAfter descending sort:\n");
    for (i = 0; i < 5; i++) {
        uuid_format(&uuids[i], buf, sizeof(buf));
        printf("  [%d] %s\n", i, buf);
    }

    return 0;
}
```

## Output

```
uuid v0.1.0 - Comparison & Sorting Example

Before sorting:
  [0] 00000000-0000-0000-0000-000000000000
  [1] 8a9bdf5e-a889-4ccf-b472-29037c88eba2
  [2] 992cd854-7da8-4d6a-9293-e49d7c6a879b
  [3] c68a987a-bb57-4690-965e-b48b947cf90c
  [4] ffffffff-ffff-ffff-ffff-ffffffffffff

After ascending sort:
  [0] 00000000-0000-0000-0000-000000000000
  [1] 8a9bdf5e-a889-4ccf-b472-29037c88eba2
  [2] 992cd854-7da8-4d6a-9293-e49d7c6a879b
  [3] c68a987a-bb57-4690-965e-b48b947cf90c
  [4] ffffffff-ffff-ffff-ffff-ffffffffffff

After descending sort:
  [0] ffffffff-ffff-ffff-ffff-ffffffffffff
  [1] c68a987a-bb57-4690-965e-b48b947cf90c
  [2] 992cd854-7da8-4d6a-9293-e49d7c6a879b
  [3] 8a9bdf5e-a889-4ccf-b472-29037c88eba2
  [4] 00000000-0000-0000-0000-000000000000
```