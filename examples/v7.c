/*
 * v7.c - UUID v7 (Unix epoch time-based) example
 * Copyright (c) 2026 Muhammad Fiaz - MIT License
 */

#include <uuid/uuid.h>
#include <stdio.h>

int main(void) {
    uuid_v7_state_t state;
    uuid_t uuid;
    char buf[UUID_STRING_LEN];
    uint64_t ts;
    int i;

    printf("uuid v%s - UUID v7 (Unix Epoch Time) Example\n\n", uuid_version_string());

    uuid_v7_init(&state);

    printf("Generating 5 monotonic UUIDs v7:\n");
    for (i = 0; i < 5; i++) {
        uuid_v7(&state, &uuid);
        uuid_format(&uuid, buf, sizeof(buf));
        uuid_v7_timestamp_ms(&uuid, &ts);
        printf("  %s  (ts=%llu ms)\n", buf, (unsigned long long)ts);
    }

    printf("\nVerifying sort order...\n");
    uuid_t prev, curr;
    uuid_v7_init(&state);
    uuid_v7(&state, &prev);
    for (i = 1; i < 5; i++) {
        uuid_v7(&state, &curr);
        if (uuid_compare(&prev, &curr) > 0) {
            printf("  ERROR: Not sorted!\n");
            return 1;
        }
        prev = curr;
    }
    printf("  Sorted OK\n");

    return 0;
}
