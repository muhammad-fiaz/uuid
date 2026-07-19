# Hashing

Functions for hashing UUIDs.

## uuid_hash

```c
uint64_t uuid_hash(const uuid_t *uuid);
```

FNV-1a hash of a UUID, suitable for hash tables.

```c
uuid_t key;
uuid_v4(&key);
uint64_t h = uuid_hash(&key);
size_t bucket = h % TABLE_SIZE;
```

## uuid_md5

```c
void uuid_md5(const void *data, size_t data_len, uint8_t digest[16]);
```

Compute MD5 hash. Used internally for UUID v3.

```c
uint8_t digest[16];
uuid_md5("hello", 5, digest);
```

## uuid_sha1

```c
void uuid_sha1(const void *data, size_t data_len, uint8_t digest[20]);
```

Compute SHA-1 hash. Used internally for UUID v5.

```c
uint8_t digest[20];
uuid_sha1("hello", 5, digest);
```
