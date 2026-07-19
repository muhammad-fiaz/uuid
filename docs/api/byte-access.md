# Byte Access

Functions for accessing UUID bytes.

## uuid_byte_at

```c
uuid_error_t uuid_byte_at(const uuid_t *uuid, size_t index, uint8_t *byte);
```

Get a specific byte from a UUID.

```c
uuid_t uuid;
uint8_t byte;
uuid_v4(&uuid);
uuid_byte_at(&uuid, 0, &byte);
printf("First byte: 0x%02x\n", byte);
```

## uuid_bytes

```c
const uint8_t *uuid_bytes(const uuid_t *uuid);
```

Get a pointer to the raw 16-byte array.

```c
uuid_t uuid;
uuid_v4(&uuid);
const uint8_t *raw = uuid_bytes(&uuid);
// raw[0] through raw[15] are accessible
```

## uuid_serialize

```c
uuid_error_t uuid_serialize(const uuid_t *uuid, uint8_t *buf, size_t size);
```

Copy UUID bytes to a buffer.

## uuid_deserialize

```c
uuid_error_t uuid_deserialize(uuid_t *uuid, const uint8_t *buf, size_t size);
```

Load UUID from a buffer.
