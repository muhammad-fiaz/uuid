/*
 * v6.c - UUID v6 (reordered time-based) example
 * Copyright (c) 2026 Muhammad Fiaz - MIT License
 */

#include <uuid/uuid.h>
#include <stdio.h>

int main(void) {
    uuid_v1_state_t state;
    uuid_t uuid;
    char buf[UUID_STRING_LEN];

    printf("uuid v%s - UUID v6 (Reordered Time) Example\n\n", uuid_version_string());

    uuid_v6_init(&state);

    uuid_v6(&state, &uuid);
    uuid_format(&uuid, buf, sizeof(buf));
    printf("v6: %s\n", buf);
    printf("Version: %d\n", uuid_version(&uuid));

    return 0;
}
