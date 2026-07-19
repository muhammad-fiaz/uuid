# Namespace API

Functions for working with well-known namespaces.

## uuid_namespace

```c
uuid_error_t uuid_namespace(uuid_namespace_t ns, uuid_t *uuid);
```

Get a well-known namespace UUID by enum value.

```c
uuid_t dns_ns;
uuid_namespace(UUID_NS_DNS, &dns_ns);
// dns_ns = 6ba7b810-9dad-11d1-80b4-00c04fd430c8
```

## uuid_get_namespace

```c
uuid_error_t uuid_get_namespace(uuid_namespace_t ns, uuid_t *uuid);
```

Alias for `uuid_namespace()`.

## Namespace Enum

| Enum | UUID |
|------|------|
| `UUID_NS_DNS` | `6ba7b810-9dad-11d1-80b4-00c04fd430c8` |
| `UUID_NS_URL` | `6ba7b811-9dad-11d1-80b4-00c04fd430c8` |
| `UUID_NS_OID` | `6ba7b812-9dad-11d1-80b4-00c04fd430c8` |
| `UUID_NS_X500` | `6ba7b814-9dad-11d1-80b4-00c04fd430c8` |
