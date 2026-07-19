/*
 * bench_uuid.c - Performance benchmarks for uuid library
 * Copyright (c) 2026 Muhammad Fiaz - MIT License
 */

#if defined(_WIN32)
#include <windows.h>
#endif

#include "uuid/uuid.h"

#include <stdio.h>

#if !defined(_WIN32)
#include <time.h>
#endif

#define BENCH_ITERATIONS 100000

#if defined(_WIN32)
static double time_diff_ms(LARGE_INTEGER start, LARGE_INTEGER end, LARGE_INTEGER freq) {
    return (double)(end.QuadPart - start.QuadPart) * 1000.0 / (double)freq.QuadPart;
}
#define TIME_START(var) do { QueryPerformanceCounter(&(var)); } while(0)
#define TIME_END(var) do { QueryPerformanceCounter(&(var)); } while(0)
#define TIME_DECL(var) LARGE_INTEGER var
static LARGE_INTEGER bench_freq;
static void time_init(void) { QueryPerformanceFrequency(&bench_freq); }
#define TIME_DIFF_MS(s, e) time_diff_ms((s), (e), bench_freq)
#else
static double time_diff_ms(struct timespec start, struct timespec end) {
    return (double)(end.tv_sec - start.tv_sec) * 1000.0 +
           (double)(end.tv_nsec - start.tv_nsec) / 1000000.0;
}
#define TIME_START(var) clock_gettime(CLOCK_MONOTONIC, &(var))
#define TIME_END(var) clock_gettime(CLOCK_MONOTONIC, &(var))
#define TIME_DECL(var) struct timespec var
#define TIME_DIFF_MS(s, e) time_diff_ms((s), (e))
#endif

static void bench_v4(void) {
    TIME_DECL(start), end;
    uuid_t uuid;
    int i;
    double ms;

    TIME_START(start);
    for (i = 0; i < BENCH_ITERATIONS; i++) {
        uuid_v4(&uuid);
    }
    TIME_END(end);
    ms = TIME_DIFF_MS(start, end);
    printf("  v4 generate:     %8d iterations in %8.2f ms  (%.1f us/op, %.0f ops/sec)\n",
           BENCH_ITERATIONS, ms, ms * 1000.0 / BENCH_ITERATIONS,
           BENCH_ITERATIONS * 1000.0 / ms);
}

static void bench_v7(void) {
    TIME_DECL(start), end;
    uuid_v7_state_t state;
    uuid_t uuid;
    int i;
    double ms;

    uuid_v7_init(&state);
    TIME_START(start);
    for (i = 0; i < BENCH_ITERATIONS; i++) {
        uuid_v7(&state, &uuid);
    }
    TIME_END(end);
    ms = TIME_DIFF_MS(start, end);
    printf("  v7 generate:     %8d iterations in %8.2f ms  (%.1f us/op, %.0f ops/sec)\n",
           BENCH_ITERATIONS, ms, ms * 1000.0 / BENCH_ITERATIONS,
           BENCH_ITERATIONS * 1000.0 / ms);
}

static void bench_v1(void) {
    TIME_DECL(start), end;
    uuid_v1_state_t state;
    uuid_t uuid;
    int i;
    double ms;

    uuid_v1_init(&state);
    TIME_START(start);
    for (i = 0; i < BENCH_ITERATIONS; i++) {
        uuid_v1(&state, &uuid);
    }
    TIME_END(end);
    ms = TIME_DIFF_MS(start, end);
    printf("  v1 generate:     %8d iterations in %8.2f ms  (%.1f us/op, %.0f ops/sec)\n",
           BENCH_ITERATIONS, ms, ms * 1000.0 / BENCH_ITERATIONS,
           BENCH_ITERATIONS * 1000.0 / ms);
}

static void bench_v5(void) {
    TIME_DECL(start), end;
    uuid_t ns, uuid;
    int i;
    double ms;

    uuid_namespace(UUID_NS_DNS, &ns);
    TIME_START(start);
    for (i = 0; i < BENCH_ITERATIONS; i++) {
        uuid_v5(&ns, "example.com", 11, &uuid);
    }
    TIME_END(end);
    ms = TIME_DIFF_MS(start, end);
    printf("  v5 generate:     %8d iterations in %8.2f ms  (%.1f us/op, %.0f ops/sec)\n",
           BENCH_ITERATIONS, ms, ms * 1000.0 / BENCH_ITERATIONS,
           BENCH_ITERATIONS * 1000.0 / ms);
}

static void bench_parse(void) {
    TIME_DECL(start), end;
    uuid_t uuid;
    int i;
    double ms;
    const char *str = "550e8400-e29b-41d4-a716-446655440000";

    TIME_START(start);
    for (i = 0; i < BENCH_ITERATIONS; i++) {
        uuid_parse(&uuid, str);
    }
    TIME_END(end);
    ms = TIME_DIFF_MS(start, end);
    printf("  parse:           %8d iterations in %8.2f ms  (%.1f us/op, %.0f ops/sec)\n",
           BENCH_ITERATIONS, ms, ms * 1000.0 / BENCH_ITERATIONS,
           BENCH_ITERATIONS * 1000.0 / ms);
}

static void bench_format(void) {
    TIME_DECL(start), end;
    uuid_t uuid;
    char buf[UUID_STRING_LEN];
    int i;
    double ms;

    uuid_parse(&uuid, "550e8400-e29b-41d4-a716-446655440000");
    TIME_START(start);
    for (i = 0; i < BENCH_ITERATIONS; i++) {
        uuid_format(&uuid, buf, sizeof(buf));
    }
    TIME_END(end);
    ms = TIME_DIFF_MS(start, end);
    printf("  format:          %8d iterations in %8.2f ms  (%.1f us/op, %.0f ops/sec)\n",
           BENCH_ITERATIONS, ms, ms * 1000.0 / BENCH_ITERATIONS,
           BENCH_ITERATIONS * 1000.0 / ms);
}

static void bench_compare(void) {
    TIME_DECL(start), end;
    uuid_t a, b;
    int i;
    double ms;

    uuid_v4(&a);
    uuid_v4(&b);
    TIME_START(start);
    for (i = 0; i < BENCH_ITERATIONS; i++) {
        uuid_compare(&a, &b);
    }
    TIME_END(end);
    ms = TIME_DIFF_MS(start, end);
    printf("  compare:         %8d iterations in %8.2f ms  (%.1f us/op, %.0f ops/sec)\n",
           BENCH_ITERATIONS, ms, ms * 1000.0 / BENCH_ITERATIONS,
           BENCH_ITERATIONS * 1000.0 / ms);
}

static void bench_hash(void) {
    TIME_DECL(start), end;
    uuid_t uuid;
    int i;
    double ms;

    uuid_v4(&uuid);
    TIME_START(start);
    for (i = 0; i < BENCH_ITERATIONS; i++) {
        volatile uint64_t h = uuid_hash(&uuid);
        (void)h;
    }
    TIME_END(end);
    ms = TIME_DIFF_MS(start, end);
    printf("  hash:            %8d iterations in %8.2f ms  (%.1f us/op, %.0f ops/sec)\n",
           BENCH_ITERATIONS, ms, ms * 1000.0 / BENCH_ITERATIONS,
           BENCH_ITERATIONS * 1000.0 / ms);
}

static void bench_validate(void) {
    TIME_DECL(start), end;
    int i;
    double ms;
    const char *str = "550e8400-e29b-41d4-a716-446655440000";

    TIME_START(start);
    for (i = 0; i < BENCH_ITERATIONS; i++) {
        uuid_validate(str);
    }
    TIME_END(end);
    ms = TIME_DIFF_MS(start, end);
    printf("  validate:        %8d iterations in %8.2f ms  (%.1f us/op, %.0f ops/sec)\n",
           BENCH_ITERATIONS, ms, ms * 1000.0 / BENCH_ITERATIONS,
           BENCH_ITERATIONS * 1000.0 / ms);
}

int main(void) {
#if defined(_WIN32)
    time_init();
#endif
    printf("uuid v%s - Benchmark Suite (%d iterations)\n", uuid_version_string(), BENCH_ITERATIONS);
    printf("================================================\n\n");

    bench_v4();
    bench_v7();
    bench_v1();
    bench_v5();
    bench_parse();
    bench_format();
    bench_compare();
    bench_hash();
    bench_validate();

    printf("\n================================================\n");
    printf("Done.\n");

    return 0;
}
