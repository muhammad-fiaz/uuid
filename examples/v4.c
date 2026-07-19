/*
 * v4.c - UUID v4 (random) example
 * Copyright (c) 2026 Muhammad Fiaz - MIT License
 */

#include <uuid/uuid.h>
#include <stdio.h>

int main(void) {
    uuid_t uuid;
    char buf[UUID_STRING_LEN];
    int i;

    printf("uuid v%s - UUID v4 (Random) Example\n\n", uuid_version_string());

    /* Generate 10 random UUIDs */
    printf("Generating 10 random UUIDs:\n");
    for (i = 0; i < 10; i++) {
        uuid_v4(&uuid);
        uuid_format(&uuid, buf, sizeof(buf));
        printf("  %2d. %s\n", i + 1, buf);
    }

    /* Verify all are v4 */
    printf("\nVerifying all are v4 with RFC 4122 variant...\n");
    for (i = 0; i < 10; i++) {
        uuid_v4(&uuid);
        if (uuid_version(&uuid) != 4 || uuid_variant(&uuid) != UUID_VARIANT_RFC_4122) {
            printf("  ERROR: UUID %d has wrong version/variant!\n", i + 1);
            return 1;
        }
    }
    printf("  All verified OK\n");

    return 0;
}
