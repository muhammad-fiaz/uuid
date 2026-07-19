/*
 * v8.c - UUID v8 (custom) example
 * Copyright (c) 2026 Muhammad Fiaz - MIT License
 */

#include <uuid/uuid.h>
#include <stdio.h>

int main(void) {
    uuid_t uuid;
    char buf[UUID_STRING_LEN];
    uint8_t custom[12] = {0xDE,0xAD,0xBE,0xEF,0xCA,0xFE,0xBA,0xBE,0x01,0x23,0x45,0x67};

    printf("uuid v%s - UUID v8 (Custom) Example\n\n", uuid_version_string());

    uuid_v8(&uuid, custom);
    uuid_format(&uuid, buf, sizeof(buf));
    printf("v8(custom):       %s\n", buf);
    printf("Version:          %d\n", uuid_version(&uuid));
    printf("Variant:          %d\n", uuid_variant(&uuid));

    /* Fully custom (no auto version/variant) */
    uint8_t full_custom[16] = {0xFF,0xFE,0xFD,0xFC,0xFB,0xFA,0xF9,0xF8,
                               0xF7,0xF6,0xF5,0xF4,0xF3,0xF2,0xF1,0xF0};
    uuid_v8_custom(&uuid, full_custom);
    uuid_format(&uuid, buf, sizeof(buf));
    printf("v8(full-custom):  %s\n", buf);

    return 0;
}
