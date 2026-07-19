/*
 * binary_conversion.c - Binary serialization/deserialization example
 * Copyright (c) 2026 Muhammad Fiaz - MIT License
 */

#include <uuid/uuid.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    uuid_t uuid, restored;
    char str[UUID_STRING_LEN];

    printf("uuid v%s - Binary Conversion Example\n\n", uuid_version_string());

    /* Generate a UUID */
    uuid_v4(&uuid);
    uuid_format(&uuid, str, sizeof(str));
    printf("Original:   %s\n", str);

    /* Serialize to binary buffer */
    uint8_t buffer[UUID_BINARY_SIZE];
    uuid_serialize(&uuid, buffer, sizeof(buffer));
    printf("Binary:     ");
    for (int i = 0; i < UUID_BINARY_SIZE; i++) {
        printf("%02X", buffer[i]);
    }
    printf("\n");

    /* Deserialize from binary */
    uuid_deserialize(&restored, buffer, sizeof(buffer));
    uuid_format(&restored, str, sizeof(str));
    printf("Restored:   %s\n", str);
    printf("Match:      %s\n\n", uuid_compare(&uuid, &restored) == 0 ? "yes" : "no");

    /* Direct binary access */
    printf("Direct byte access:\n");
    const uint8_t *bytes = uuid_bytes(&uuid);
    printf("  bytes[0]:  0x%02X\n", bytes[0]);
    printf("  bytes[6]:  0x%02X (version nibble: %d)\n", bytes[6], uuid_version(&uuid));
    printf("  bytes[8]:  0x%02X (variant: %d)\n\n", bytes[8], uuid_variant(&uuid));

    /* Format to binary output */
    printf("Binary format output:\n");
    uint8_t bin_out[UUID_BINARY_SIZE];
    uuid_format_binary(&uuid, bin_out, sizeof(bin_out));
    printf("  ");
    for (int i = 0; i < UUID_BINARY_SIZE; i++) {
        printf("%02X ", bin_out[i]);
    }
    printf("\n\n");

    /* Parse from binary */
    printf("Parse from binary:\n");
    uint8_t raw[16] = {0x55,0x0e,0x84,0x00,0xe2,0x9b,0x41,0xd4,
                       0xa7,0x16,0x44,0x66,0x55,0x44,0x00,0x00};
    uuid_parse_binary(&uuid, raw, sizeof(raw));
    uuid_format(&uuid, str, sizeof(str));
    printf("  %s\n", str);

    return 0;
}
