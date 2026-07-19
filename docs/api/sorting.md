# Sorting

Functions for sorting UUID arrays.

## uuid_sort_asc

```c
void uuid_sort_asc(uuid_t *uuids, size_t count);
```

Sort an array of UUIDs in ascending (byte) order.

```c
uuid_t uuids[100];
for (int i = 0; i < 100; i++) uuid_v4(&uuids[i]);
uuid_sort_asc(uuids, 100);
```

## uuid_sort_desc

```c
void uuid_sort_desc(uuid_t *uuids, size_t count);
```

Sort in descending order.

## Notes

- Uses qsort internally
- For v7 UUIDs, ascending byte order = chronological order
- For v4 UUIDs, sort order has no semantic meaning
- Thread-safe (no shared state)
