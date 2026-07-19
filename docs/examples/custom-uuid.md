---
title: Custom UUID Example
description: Create UUIDs from explicit bytes, custom data, and special UUIDs.
---

# Custom UUID Example

Create UUIDs from explicit bytes, custom data, and special UUIDs.

## Source Code

```c
/*
 * custom_uuid.c - Custom UUID creation example
 * Copyright (c) 2026 Muhammad Fiaz - MIT License
 */

#include <uuid/uuid.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    uuid_t uuid;

    printf("uuid v%s - Custom UUID Example\n\n", uuid_version_string());

    /* Create UUID from explicit bytes */
    printf("1. Create from explicit bytes:\n");
    uint8_t raw[16] = {0xDE,0xAD,0xBE,0xEF,0xCA,0xFE,0xBA,0xBE,
                       0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF};
    uuid_init_from_bytes(&uuid, raw);
    char buf[UUID_STRING_LEN];
    uuid_format(&uuid, buf, sizeof(buf));
    printf("   %s\n\n", buf);

    /* Create UUID v8 with 12 custom bytes */
    printf("2. UUID v8 with custom data:\n");
    uint8_t custom12[12] = {0xAA,0xBB,0xCC,0xDD,0xEE,0xFF,
                            0x11,0x22,0x33,0x44,0x55,0x66};
    uuid_v8(&uuid, custom12);
    uuid_format(&uuid, buf, sizeof(buf));
    printf("   %s\n", buf);
    printf("   Version: %d, Variant: %d\n\n", uuid_version(&uuid), uuid_variant(&uuid));

    /* Create UUID v8 with 16 custom bytes (full control) */
    printf("3. UUID v8 with full 16-byte custom data:\n");
    uint8_t custom16[16] = {0xFF,0xFE,0xFD,0xFC,0xFB,0xFA,0xF9,0xF8,
                            0xF7,0xF6,0xF5,0xF4,0xF3,0xF2,0xF1,0xF0};
    uuid_v8_custom(&uuid, custom16);
    uuid_format(&uuid, buf, sizeof(buf));
    printf("   %s\n\n", buf);

    /* Nil and Max UUIDs */
    printf("4. Special UUIDs:\n");
    uuid_init_nil(&uuid);
    uuid_format(&uuid, buf, sizeof(buf));
    printf("   Nil:     %s\n", buf);

    uuid_init_max(&uuid);
    uuid_format(&uuid, buf, sizeof(buf));
    printf("   Max:     %s\n\n", buf);

    /* Copy and compare custom UUIDs */
    printf("5. Copy and compare:\n");
    uuid_t a, b;
    uint8_t data_a[16] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
                          0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10};
    uuid_init_from_bytes(&a, data_a);
    uuid_copy(&b, &a);
    uuid_format(&a, buf, sizeof(buf));
    printf("   Original: %s\n", buf);
    uuid_format(&b, buf, sizeof(buf));
    printf("   Copy:     %s\n", buf);
    printf("   Equal:    %s\n", uuid_compare(&a, &b) == 0 ? "yes" : "no");

    return 0;
}
```

## Output

```
uuid v0.1.0 - Custom UUID Example

1. Create from explicit bytes:
   deadbeef-cafe-babe-8123-456789abcdef

2. UUID v8 with custom data:
   aabbccdd-eeff-8122-9344-556600000000
   Version: 8, Variant: 1

3. UUID v8 with full 16-byte custom data:
   fffefdfc-fbfa-f9f8-f7f6-f5f4f3f2f1f0

4. Special UUIDs:
   Nil:     00000000-0000-0000-0000-000000000000
   Max:     ffffffff-ffff-ffff-ffff-ffffffffffff

5. Copy and compare:
   Original: 01020304-0506-0708-090a-0b0c0d0e0f10
   Copy:     01020304-0506-0708-090a-0b0c0d0e0f10
   Equal:    yes
```
