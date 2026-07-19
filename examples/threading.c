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
