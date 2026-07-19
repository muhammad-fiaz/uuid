# Comparison

Functions for comparing UUIDs.

## uuid_compare

```c
int uuid_compare(const uuid_t *a, const uuid_t *b);
```

Compare two UUIDs byte-by-byte.

**Returns:** < 0 if a < b, 0 if a == b, > 0 if a > b

```c
uuid_t a, b;
uuid_v4(&a);
uuid_v4(&b);

int cmp = uuid_compare(&a, &b);
if (cmp < 0) printf("a < b\n");
else if (cmp == 0) printf("a == b\n");
else printf("a > b\n");
```

## uuid_compare_asc

```c
int uuid_compare_asc(const void *a, const void *b);
```

qsort-compatible comparator for ascending order.

```c
uuid_t uuids[100];
// ... fill uuids ...
qsort(uuids, 100, sizeof(uuid_t), uuid_compare_asc);
```

## uuid_compare_desc

```c
int uuid_compare_desc(const void *a, const void *b);
```

qsort-compatible comparator for descending order.

## uuid_is_nil

```c
int uuid_is_nil(const uuid_t *uuid);
```

Returns 1 if UUID is nil (all zeros), 0 otherwise.

## uuid_is_max

```c
int uuid_is_max(const uuid_t *uuid);
```

Returns 1 if UUID is max (all 0xFF), 0 otherwise.
