# Namespaces

Well-known namespace UUIDs for name-based UUID generation (v3 and v5).

## Well-Known Namespaces

| Enum | Name | UUID |
|------|------|------|
| `UUID_NS_DNS` | Domain Name System | `6ba7b810-9dad-11d1-80b4-00c04fd430c8` |
| `UUID_NS_URL` | URL | `6ba7b811-9dad-11d1-80b4-00c04fd430c8` |
| `UUID_NS_OID` | ISO OID | `6ba7b812-9dad-11d1-80b4-00c04fd430c8` |
| `UUID_NS_X500` | X.500 DN | `6ba7b814-9dad-11d1-80b4-00c04fd430c8` |

## Usage

```c
#include <uuid/uuid.h>

uuid_t uuid;
char buf[UUID_STRING_LEN];

// DNS namespace
uuid_v5_ns(UUID_NS_DNS, "example.com", 11, &uuid);
uuid_format(&uuid, buf, sizeof(buf));

// URL namespace
uuid_v5_ns(UUID_NS_URL, "https://example.com/path", 24, &uuid);

// Get namespace UUID
uuid_t ns;
uuid_namespace(UUID_NS_DNS, &ns);
```

## Custom Namespaces

```c
#include <uuid/uuid.h>

// Create a custom namespace UUID
uuid_t custom_ns;
uuid_v4(&custom_ns);

// Use it with v3 or v5
uuid_t uuid;
uuid_v5(&custom_ns, "my-app-entity", 13, &uuid);
```
