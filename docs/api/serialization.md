# Serialization

Functions for binary serialization/deserialization.

## uuid_serialize

```c
uuid_error_t uuid_serialize(const uuid_t *uuid, uint8_t *buf, size_t size);
```

Serialize a UUID to a 16-byte buffer.

```c
uuid_t uuid;
uint8_t buf[16];
uuid_v4(&uuid);
uuid_serialize(&uuid, buf, sizeof(buf));
// buf now contains 16 bytes of the UUID
```

## uuid_deserialize

```c
uuid_error_t uuid_deserialize(uuid_t *uuid, const uint8_t *buf, size_t size);
```

Deserialize a UUID from a 16-byte buffer.

```c
uint8_t buf[16]; // ... loaded from somewhere ...
uuid_t uuid;
uuid_deserialize(&uuid, buf, sizeof(buf));
```

## Use Cases

- Network transmission
- Database storage
- File I/O
- Inter-process communication
