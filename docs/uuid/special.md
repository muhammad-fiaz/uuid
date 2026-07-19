# Nil & Max UUID

Special-purpose sentinel UUIDs.

## Nil UUID

The Nil UUID is all zeros: `00000000-0000-0000-0000-000000000000`

```c
#include <uuid/uuid.h>

uuid_t nil_uuid;
uuid_init_nil(&nil_uuid);

// Or use the static constant
uuid_t nil = UUID_NIL;

// Check if a UUID is nil
if (uuid_is_nil(&uuid)) {
    printf("UUID is nil\n");
}
```

## Max UUID

The Max UUID is all 0xFF: `ffffffff-ffff-ffff-ffff-ffffffffffff`

```c
#include <uuid/uuid.h>

uuid_t max_uuid;
uuid_init_max(&max_uuid);

// Or use the static constant
uuid_t max = UUID_MAX_UUID;

// Check if a UUID is max
if (uuid_is_max(&uuid)) {
    printf("UUID is max\n");
}
```

## Formatting

```c
char buf[UUID_STRING_LEN];

uuid_format(&UUID_NIL, buf, sizeof(buf));
// buf = "00000000-0000-0000-0000-000000000000"

uuid_format(&UUID_MAX_UUID, buf, sizeof(buf));
// buf = "ffffffff-ffff-ffff-ffff-ffffffffffff"
```

## Comparison

Nil UUID sorts before all other UUIDs. Max UUID sorts after all other UUIDs:

```c
uuid_t a, b;
uuid_v4(&a);
uuid_init_nil(&b);
uuid_compare(&b, &a);  // < 0 (nil < any)

uuid_init_max(&b);
uuid_compare(&a, &b);  // < 0 (any < max)
```
