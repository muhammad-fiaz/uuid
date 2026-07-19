/*
 * parsing.c - UUID parsing examples
 * Copyright (c) 2026 Muhammad Fiaz - MIT License
 */

#include <uuid/uuid.h>
#include <stdio.h>

int main(void) {
    uuid_t uuid;
    char buf[UUID_STRING_LEN];
    const char *inputs[] = {
        "550e8400-e29b-41d4-a716-446655440000",
        "550E8400-E29B-41D4-A716-446655440000",
        "550e8400e29b41d4a716446655440000",
        "{550e8400-e29b-41d4-a716-446655440000}",
        "00000000-0000-0000-0000-000000000000",
        "ffffffff-ffff-ffff-ffff-ffffffffffff",
        "invalid-uuid-string",
        "",
        NULL
    };
    int i;

    printf("uuid v%s - Parsing Example\n\n", uuid_version_string());

    for (i = 0; inputs[i]; i++) {
        uuid_error_t err = uuid_parse(&uuid, inputs[i]);
        if (err == UUID_OK) {
            uuid_format(&uuid, buf, sizeof(buf));
            printf("  OK:   \"%s\" -> %s\n", inputs[i], buf);
        } else {
            printf("  FAIL: \"%s\" -> %s\n", inputs[i], uuid_strerror(err));
        }
    }

    /* Validate only */
    printf("\nValidate only:\n");
    const char *valid = "550e8400-e29b-41d4-a716-446655440000";
    const char *invalid = "not-a-uuid";
    printf("  \"%s\": %s\n", valid,
           uuid_validate(valid) == UUID_OK ? "valid" : "invalid");
    printf("  \"%s\": %s\n", invalid,
           uuid_validate(invalid) == UUID_OK ? "valid" : "invalid");

    return 0;
}
