/*
 * v5.c - UUID v5 (SHA-1 name-based) example
 * Copyright (c) 2026 Muhammad Fiaz - MIT License
 */

#include <uuid/uuid.h>
#include <stdio.h>

int main(void) {
    uuid_t uuid;
    char buf[UUID_STRING_LEN];

    printf("uuid v%s - UUID v5 (SHA-1 Name-based) Example\n\n", uuid_version_string());

    uuid_v5_ns(UUID_NS_DNS, "example.com", 11, &uuid);
    uuid_format(&uuid, buf, sizeof(buf));
    printf("v5(DNS, \"example.com\"):    %s\n", buf);

    uuid_v5_ns(UUID_NS_DNS, "example.com", 11, &uuid);
    printf("v5(DNS, \"example.com\"):    %s  (same)\n", buf);

    uuid_v5_ns(UUID_NS_URL, "https://example.com", 18, &uuid);
    uuid_format(&uuid, buf, sizeof(buf));
    printf("v5(URL, \"https://...com\"): %s\n", buf);

    return 0;
}
