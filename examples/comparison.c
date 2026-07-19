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
