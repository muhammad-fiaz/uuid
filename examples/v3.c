/*
 * v3.c - UUID v3 (MD5 name-based) example
 * Copyright (c) 2026 Muhammad Fiaz - MIT License
 */

#include <uuid/uuid.h>
#include <stdio.h>

int main(void) {
    uuid_t uuid;
    char buf[UUID_STRING_LEN];

    printf("uuid v%s - UUID v3 (MD5 Name-based) Example\n\n", uuid_version_string());

    /* Generate UUID v3 with DNS namespace */
    uuid_v3_ns(UUID_NS_DNS, "example.com", 11, &uuid);
    uuid_format(&uuid, buf, sizeof(buf));
    printf("v3(DNS, \"example.com\"):    %s\n", buf);

    /* Same input = same UUID (deterministic) */
    uuid_v3_ns(UUID_NS_DNS, "example.com", 11, &uuid);
    printf("v3(DNS, \"example.com\"):    %s  (same)\n", buf);

    /* Different name = different UUID */
    uuid_v3_ns(UUID_NS_DNS, "example.org", 11, &uuid);
    uuid_format(&uuid, buf, sizeof(buf));
    printf("v3(DNS, \"example.org\"):    %s\n", buf);

    /* URL namespace */
    uuid_v3_ns(UUID_NS_URL, "https://example.com", 18, &uuid);
    uuid_format(&uuid, buf, sizeof(buf));
    printf("v3(URL, \"https://...com\"): %s\n", buf);

    /* Custom namespace */
    uuid_t ns;
    uuid_v4(&ns);
    uuid_v3(&ns, "custom-name", 11, &uuid);
    uuid_format(&uuid, buf, sizeof(buf));
    printf("v3(custom-ns, \"custom\"):   %s\n", buf);

    return 0;
}
