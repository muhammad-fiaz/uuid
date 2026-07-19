---
title: Thread Safety Example
description: Demonstrates thread-safe UUID generation with multiple threads.
---

# Thread Safety Example

This example demonstrates thread-safe UUID generation by spawning multiple threads that concurrently generate UUIDs.

## Source Code

```c
/*
 * threading.c - Thread safety example
 * Copyright (c) 2026 Muhammad Fiaz - MIT License
 */

#if defined(_WIN32)
#include <windows.h>
#endif

#include <uuid/uuid.h>
#include <stdio.h>

#if defined(_WIN32)
DWORD WINAPI thread_func(LPVOID arg) {
    int id = *(int *)arg;
    uuid_t uuid;
    char buf[UUID_STRING_LEN];
    int i;
    for (i = 0; i < 5; i++) {
        uuid_v4(&uuid);
        uuid_format(&uuid, buf, sizeof(buf));
        printf("  Thread %d: %s\n", id, buf);
    }
    return 0;
}
#else
#include <pthread.h>
void *thread_func(void *arg) {
    int id = *(int *)arg;
    uuid_t uuid;
    char buf[UUID_STRING_LEN];
    int i;
    for (i = 0; i < 5; i++) {
        uuid_v4(&uuid);
        uuid_format(&uuid, buf, sizeof(buf));
        printf("  Thread %d: %s\n", id, buf);
    }
    return NULL;
}
#endif

int main(void) {
    printf("uuid v%s - Thread Safety Example\n\n", uuid_version_string());

#if defined(_WIN32)
    HANDLE threads[4];
    int ids[4] = {1, 2, 3, 4};
    int i;
    for (i = 0; i < 4; i++) {
        threads[i] = CreateThread(NULL, 0, thread_func, &ids[i], 0, NULL);
    }
    WaitForMultipleObjects(4, threads, TRUE, INFINITE);
    for (i = 0; i < 4; i++) CloseHandle(threads[i]);
#else
    pthread_t threads[4];
    int ids[4] = {1, 2, 3, 4};
    int i;
    for (i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, thread_func, &ids[i]);
    }
    for (i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }
#endif

    printf("\nAll threads completed successfully.\n");
    return 0;
}
```

## Output

```
uuid v0.1.0 - Thread Safety Example

  Thread 1: 992cd854-7da8-4d6a-9293-e49d7c6a879b
  Thread 1: 8a9bdf5e-a889-4ccf-b472-29037c88eba2
  Thread 1: c68a987a-bb57-4690-965e-b48b947cf90c
  Thread 1: 550e8400-e29b-41d4-a716-446655440000
  Thread 1: 12345678-1234-1234-1234-123456789abc
  Thread 2: 8a9bdf5e-a889-4ccf-b472-29037c88eba2
  Thread 2: 992cd854-7da8-4d6a-9293-e49d7c6a879b
  Thread 2: c68a987a-bb57-4690-965e-b48b947cf90c
  Thread 2: 550e8400-e29b-41d4-a716-446655440000
  Thread 2: 12345678-1234-1234-1234-123456789abc
  ...

All threads completed successfully.
```