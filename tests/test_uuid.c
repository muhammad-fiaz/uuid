/*
 * test_uuid.c - Comprehensive test suite for uuid library
 *
 * Copyright (c) 2026 Muhammad Fiaz
 * SPDX-License-Identifier: MIT
 */

#include "uuid/uuid.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int tests_run = 0;
static int tests_passed = 0;
static int tests_failed = 0;

#define TEST(name) \
    static void test_##name(void); \
    static void run_##name(void) { \
        tests_run++; \
        printf("  [%d] %-40s", tests_run, #name); \
        test_##name(); \
        tests_passed++; \
        printf(" PASS\n"); \
    } \
    static void test_##name(void)

#define ASSERT(cond) do { \
    if (!(cond)) { \
        printf(" FAIL\n    Assert failed: %s (%s:%d)\n", #cond, __FILE__, __LINE__); \
        tests_failed++; \
        return; \
    } \
} while(0)

#define ASSERT_EQ(a, b) do { \
    int _a = (a), _b = (b); \
    if (_a != _b) { \
        printf(" FAIL\n    Assert failed: %s == %s (%d != %d) (%s:%d)\n", #a, #b, _a, _b, __FILE__, __LINE__); \
        tests_failed++; \
        return; \
    } \
} while(0)

#define ASSERT_OK(expr) do { \
    uuid_error_t _e = (expr); \
    if (_e != UUID_OK) { \
        printf(" FAIL\n    Assert OK failed: %s (error %d) (%s:%d)\n", #expr, _e, __FILE__, __LINE__); \
        tests_failed++; \
        return; \
    } \
} while(0)

#define ASSERT_STR_EQ(a, b) do { \
    if (strcmp((a), (b)) != 0) { \
        printf(" FAIL\n    Assert failed: \"%s\" != \"%s\" (%s:%d)\n", (a), (b), __FILE__, __LINE__); \
        tests_failed++; \
        return; \
    } \
} while(0)

/* ── Nil UUID Tests ────────────────────────────────────────────────────── */

TEST(nil_init) {
    uuid_t uuid;
    ASSERT_OK(uuid_init_nil(&uuid));
    ASSERT(uuid_is_nil(&uuid));
}

TEST(nil_max) {
    uuid_t uuid;
    ASSERT_OK(uuid_init_max(&uuid));
    ASSERT(uuid_is_max(&uuid));
}

TEST(nil_format) {
    uuid_t uuid;
    char buf[UUID_STRING_LEN];
    uuid_init_nil(&uuid);
    ASSERT_OK(uuid_format(&uuid, buf, sizeof(buf)));
    ASSERT_STR_EQ(buf, "00000000-0000-0000-0000-000000000000");
}

TEST(max_format) {
    uuid_t uuid;
    char buf[UUID_STRING_LEN];
    uuid_init_max(&uuid);
    ASSERT_OK(uuid_format(&uuid, buf, sizeof(buf)));
    ASSERT_STR_EQ(buf, "ffffffff-ffff-ffff-ffff-ffffffffffff");
}

/* ── v4 (Random) Tests ────────────────────────────────────────────────── */

TEST(v4_generation) {
    uuid_t uuid;
    ASSERT_OK(uuid_v4(&uuid));
    ASSERT(!uuid_is_nil(&uuid));
    ASSERT_EQ(uuid_version(&uuid), 4);
    ASSERT_EQ(uuid_variant(&uuid), UUID_VARIANT_RFC_4122);
}

TEST(v4_uniqueness) {
    uuid_t a, b;
    ASSERT_OK(uuid_v4(&a));
    ASSERT_OK(uuid_v4(&b));
    ASSERT(uuid_compare(&a, &b) != 0);
}

TEST(v4_format) {
    uuid_t uuid;
    char buf[UUID_STRING_LEN];
    ASSERT_OK(uuid_v4(&uuid));
    ASSERT_OK(uuid_format(&uuid, buf, sizeof(buf)));
    ASSERT(strlen(buf) == UUID_STRING_LEN_NO_NUL);
    ASSERT(buf[8] == '-');
    ASSERT(buf[13] == '-');
    ASSERT(buf[18] == '-');
    ASSERT(buf[23] == '-');
    ASSERT(buf[36] == '\0');
}

TEST(v4_version_nibble) {
    uuid_t uuid;
    ASSERT_OK(uuid_v4(&uuid));
    /* Byte 6 high nibble must be 4 */
    ASSERT((uuid.bytes[6] & 0xF0) == 0x40);
}

TEST(v4_variant_bits) {
    uuid_t uuid;
    ASSERT_OK(uuid_v4(&uuid));
    /* Byte 8 high 2 bits must be 10 */
    ASSERT((uuid.bytes[8] & 0xC0) == 0x80);
}

TEST(v4_many_unique) {
    uuid_t uuids[100];
    int i, j;
    for (i = 0; i < 100; i++) {
        ASSERT_OK(uuid_v4(&uuids[i]));
    }
    for (i = 0; i < 100; i++) {
        ASSERT_EQ(uuid_version(&uuids[i]), 4);
        for (j = i + 1; j < 100; j++) {
            ASSERT(uuid_compare(&uuids[i], &uuids[j]) != 0);
        }
    }
}

/* ── v1 (Time-based) Tests ────────────────────────────────────────────── */

TEST(v1_generation) {
    uuid_v1_state_t state;
    uuid_t uuid;
    ASSERT_OK(uuid_v1_init(&state));
    ASSERT_OK(uuid_v1(&state, &uuid));
    ASSERT_EQ(uuid_version(&uuid), 1);
    ASSERT_EQ(uuid_variant(&uuid), UUID_VARIANT_RFC_4122);
}

TEST(v1_timestamp_extract) {
    uuid_v1_state_t state;
    uuid_t uuid;
    uint64_t ts;
    ASSERT_OK(uuid_v1_init(&state));
    ASSERT_OK(uuid_v1(&state, &uuid));
    ASSERT_OK(uuid_v1_timestamp(&uuid, &ts));
    ASSERT(ts > 0);
}

TEST(v1_clock_seq_extract) {
    uuid_v1_state_t state;
    uuid_t uuid;
    uint16_t cs;
    ASSERT_OK(uuid_v1_init(&state));
    ASSERT_OK(uuid_v1(&state, &uuid));
    ASSERT_OK(uuid_v1_clock_seq(&uuid, &cs));
    ASSERT((cs & 0xC000) == 0); /* 14-bit value */
}

TEST(v1_node_extract) {
    uuid_v1_state_t state;
    uuid_t uuid;
    uint8_t node[6];
    ASSERT_OK(uuid_v1_init(&state));
    ASSERT_OK(uuid_v1(&state, &uuid));
    ASSERT_OK(uuid_v1_node(&uuid, node));
    /* Multicast bit should be set (random node) */
    ASSERT((node[0] & 0x01) == 1);
}

TEST(v1_monotonic) {
    uuid_v1_state_t state;
    uuid_t a, b;
    ASSERT_OK(uuid_v1_init(&state));
    ASSERT_OK(uuid_v1(&state, &a));
    ASSERT_OK(uuid_v1(&state, &b));
    /* b should be >= a (monotonic) */
    ASSERT(uuid_compare(&a, &b) <= 0);
}

/* ── v6 (Reordered time) Tests ────────────────────────────────────────── */

TEST(v6_generation) {
    uuid_v1_state_t state;
    uuid_t uuid;
    ASSERT_OK(uuid_v6_init(&state));
    ASSERT_OK(uuid_v6(&state, &uuid));
    ASSERT_EQ(uuid_version(&uuid), 6);
    ASSERT_EQ(uuid_variant(&uuid), UUID_VARIANT_RFC_4122);
}

TEST(v6_monotonic) {
    uuid_v1_state_t state;
    uuid_t a, b;
    ASSERT_OK(uuid_v6_init(&state));
    ASSERT_OK(uuid_v6(&state, &a));
    ASSERT_OK(uuid_v6(&state, &b));
    /* v6 should be sortable like v7 */
    ASSERT(uuid_compare(&a, &b) <= 0);
}

/* ── v7 (Unix epoch time) Tests ───────────────────────────────────────── */

TEST(v7_generation) {
    uuid_v7_state_t state;
    uuid_t uuid;
    ASSERT_OK(uuid_v7_init(&state));
    ASSERT_OK(uuid_v7(&state, &uuid));
    ASSERT_EQ(uuid_version(&uuid), 7);
    ASSERT_EQ(uuid_variant(&uuid), UUID_VARIANT_RFC_4122);
}

TEST(v7_timestamp_extract) {
    uuid_v7_state_t state;
    uuid_t uuid;
    uint64_t ts;
    ASSERT_OK(uuid_v7_init(&state));
    ASSERT_OK(uuid_v7(&state, &uuid));
    ASSERT_OK(uuid_v7_timestamp_ms(&uuid, &ts));
    ASSERT(ts > 0);
}

TEST(v7_monotonic) {
    uuid_v7_state_t state;
    uuid_t a, b;
    ASSERT_OK(uuid_v7_init(&state));
    ASSERT_OK(uuid_v7(&state, &a));
    ASSERT_OK(uuid_v7(&state, &b));
    ASSERT(uuid_compare(&a, &b) <= 0);
}

TEST(v7_sortable) {
    uuid_v7_state_t state;
    uuid_t a, b;
    ASSERT_OK(uuid_v7_init(&state));
    ASSERT_OK(uuid_v7(&state, &a));
    ASSERT_OK(uuid_v7(&state, &b));
    /* Same timestamp: b should be > a due to counter */
    ASSERT(uuid_compare(&a, &b) <= 0);
}

TEST(v7_many) {
    uuid_v7_state_t state;
    uuid_t uuids[50];
    int i;
    ASSERT_OK(uuid_v7_init(&state));
    for (i = 0; i < 50; i++) {
        ASSERT_OK(uuid_v7(&state, &uuids[i]));
    }
    for (i = 1; i < 50; i++) {
        ASSERT(uuid_compare(&uuids[i-1], &uuids[i]) <= 0);
    }
}

/* ── v8 (Custom) Tests ────────────────────────────────────────────────── */

TEST(v8_generation) {
    uuid_t uuid;
    uint8_t custom[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
    ASSERT_OK(uuid_v8(&uuid, custom));
    ASSERT_EQ(uuid_version(&uuid), 8);
    ASSERT_EQ(uuid_variant(&uuid), UUID_VARIANT_RFC_4122);
}

TEST(v8_custom_bytes) {
    uuid_t uuid;
    uint8_t custom[16] = {0xDE,0xAD,0xBE,0xEF,0xCA,0xFE,0xBA,0xBE,
                          0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF};
    ASSERT_OK(uuid_v8_custom(&uuid, custom));
    ASSERT(memcmp(uuid.bytes, custom, 16) == 0);
}

TEST(v8_custom_data_preserved) {
    uuid_t uuid;
    uint8_t custom[12] = {0xAA,0xBB,0xCC,0xDD,0xEE,0xFF,0x11,0x22,0x33,0x44,0x55,0x66};
    ASSERT_OK(uuid_v8(&uuid, custom));
    uint8_t expected[12];
    memcpy(expected, custom, 12);
    expected[6] = (uint8_t)((custom[6] & 0x0F) | 0x80);
    expected[8] = (uint8_t)((custom[8] & 0x3F) | 0x80);
    ASSERT(memcmp(uuid.bytes, expected, 12) == 0);
}

/* ── v3 (MD5 Name-based) Tests ────────────────────────────────────────── */

TEST(v3_generation) {
    uuid_t ns, uuid;
    ASSERT_OK(uuid_namespace(UUID_NS_DNS, &ns));
    ASSERT_OK(uuid_v3(&ns, "example.com", 11, &uuid));
    ASSERT_EQ(uuid_version(&uuid), 3);
    ASSERT_EQ(uuid_variant(&uuid), UUID_VARIANT_RFC_4122);
}

TEST(v3_deterministic) {
    uuid_t ns, a, b;
    ASSERT_OK(uuid_namespace(UUID_NS_DNS, &ns));
    ASSERT_OK(uuid_v3(&ns, "example.com", 11, &a));
    ASSERT_OK(uuid_v3(&ns, "example.com", 11, &b));
    ASSERT(uuid_compare(&a, &b) == 0);
}

TEST(v3_different_names) {
    uuid_t ns, a, b;
    ASSERT_OK(uuid_namespace(UUID_NS_DNS, &ns));
    ASSERT_OK(uuid_v3(&ns, "example.com", 11, &a));
    ASSERT_OK(uuid_v3(&ns, "example.org", 11, &b));
    ASSERT(uuid_compare(&a, &b) != 0);
}

TEST(v3_ns_dns) {
    uuid_t uuid;
    ASSERT_OK(uuid_v3_ns(UUID_NS_DNS, "example.com", 11, &uuid));
    ASSERT_EQ(uuid_version(&uuid), 3);
}

TEST(v3_ns_url) {
    uuid_t uuid;
    ASSERT_OK(uuid_v3_ns(UUID_NS_URL, "https://example.com", 18, &uuid));
    ASSERT_EQ(uuid_version(&uuid), 3);
}

/* ── v5 (SHA-1 Name-based) Tests ──────────────────────────────────────── */

TEST(v5_generation) {
    uuid_t ns, uuid;
    ASSERT_OK(uuid_namespace(UUID_NS_DNS, &ns));
    ASSERT_OK(uuid_v5(&ns, "example.com", 11, &uuid));
    ASSERT_EQ(uuid_version(&uuid), 5);
    ASSERT_EQ(uuid_variant(&uuid), UUID_VARIANT_RFC_4122);
}

TEST(v5_deterministic) {
    uuid_t ns, a, b;
    ASSERT_OK(uuid_namespace(UUID_NS_DNS, &ns));
    ASSERT_OK(uuid_v5(&ns, "example.com", 11, &a));
    ASSERT_OK(uuid_v5(&ns, "example.com", 11, &b));
    ASSERT(uuid_compare(&a, &b) == 0);
}

TEST(v5_different_from_v3) {
    uuid_t ns, a, b;
    ASSERT_OK(uuid_namespace(UUID_NS_DNS, &ns));
    ASSERT_OK(uuid_v3(&ns, "example.com", 11, &a));
    ASSERT_OK(uuid_v5(&ns, "example.com", 11, &b));
    /* v3 and v5 produce different UUIDs for the same input */
    ASSERT(uuid_compare(&a, &b) != 0);
}

TEST(v5_ns_dns) {
    uuid_t uuid;
    ASSERT_OK(uuid_v5_ns(UUID_NS_DNS, "example.com", 11, &uuid));
    ASSERT_EQ(uuid_version(&uuid), 5);
}

/* ── Parsing Tests ─────────────────────────────────────────────────────── */

TEST(parse_canonical) {
    uuid_t uuid;
    ASSERT_OK(uuid_parse(&uuid, "550e8400-e29b-41d4-a716-446655440000"));
    ASSERT_EQ(uuid.bytes[0], 0x55);
    ASSERT_EQ(uuid.bytes[1], 0x0e);
    ASSERT_EQ(uuid.bytes[2], 0x84);
    ASSERT_EQ(uuid.bytes[3], 0x00);
}

TEST(parse_uppercase) {
    uuid_t uuid;
    ASSERT_OK(uuid_parse(&uuid, "550E8400-E29B-41D4-A716-446655440000"));
    ASSERT_EQ(uuid.bytes[0], 0x55);
}

TEST(parse_mixedcase) {
    uuid_t uuid;
    ASSERT_OK(uuid_parse(&uuid, "550e8400-E29B-41d4-a716-446655440000"));
}

TEST(parse_compact) {
    uuid_t uuid;
    ASSERT_OK(uuid_parse(&uuid, "550e8400e29b41d4a716446655440000"));
    ASSERT_EQ(uuid.bytes[0], 0x55);
}

TEST(parse_braces) {
    uuid_t uuid;
    ASSERT_OK(uuid_parse(&uuid, "{550e8400-e29b-41d4-a716-446655440000}"));
    ASSERT_EQ(uuid.bytes[0], 0x55);
}

TEST(parse_nil) {
    uuid_t uuid;
    ASSERT_OK(uuid_parse(&uuid, "00000000-0000-0000-0000-000000000000"));
    ASSERT(uuid_is_nil(&uuid));
}

TEST(parse_max) {
    uuid_t uuid;
    ASSERT_OK(uuid_parse(&uuid, "ffffffff-ffff-ffff-ffff-ffffffffffff"));
    ASSERT(uuid_is_max(&uuid));
}

TEST(parse_invalid_length) {
    uuid_t uuid;
    ASSERT(uuid_parse(&uuid, "550e8400-e29b-41d4-a716") != UUID_OK);
}

TEST(parse_invalid_chars) {
    uuid_t uuid;
    ASSERT(uuid_parse(&uuid, "550e8400-e29b-41d4-a716-44665544000G") != UUID_OK);
}

TEST(parse_empty) {
    uuid_t uuid;
    ASSERT(uuid_parse(&uuid, "") != UUID_OK);
}

TEST(parse_trailing) {
    uuid_t uuid;
    ASSERT(uuid_parse(&uuid, "550e8400-e29b-41d4-a716-446655440000 extra") != UUID_OK);
}

TEST(parse_n_length) {
    uuid_t uuid;
    const char *str = "550e8400-e29b-41d4-a716-446655440000";
    ASSERT_OK(uuid_parse_n(&uuid, str, 36));
}

TEST(parse_binary) {
    uuid_t uuid;
    uint8_t data[16] = {0x55,0x0e,0x84,0x00,0xe2,0x9b,0x41,0xd4,
                        0xa7,0x16,0x44,0x66,0x55,0x44,0x00,0x00};
    ASSERT_OK(uuid_parse_binary(&uuid, data, 16));
    ASSERT_EQ(uuid.bytes[0], 0x55);
}

TEST(parse_binary_too_small) {
    uuid_t uuid;
    uint8_t data[8] = {0,0,0,0,0,0,0,0};
    ASSERT(uuid_parse_binary(&uuid, data, 8) != UUID_OK);
}

/* ── Formatting Tests ──────────────────────────────────────────────────── */

TEST(format_canonical) {
    uuid_t uuid;
    char buf[UUID_STRING_LEN];
    uuid_parse(&uuid, "550e8400-e29b-41d4-a716-446655440000");
    ASSERT_OK(uuid_format(&uuid, buf, sizeof(buf)));
    ASSERT_STR_EQ(buf, "550e8400-e29b-41d4-a716-446655440000");
}

TEST(format_compact) {
    uuid_t uuid;
    char buf[UUID_COMPACT_LEN];
    uuid_parse(&uuid, "550e8400-e29b-41d4-a716-446655440000");
    ASSERT_OK(uuid_format_compact(&uuid, buf, sizeof(buf)));
    ASSERT_STR_EQ(buf, "550e8400e29b41d4a716446655440000");
}

TEST(format_braces) {
    uuid_t uuid;
    char buf[39];
    uuid_parse(&uuid, "550e8400-e29b-41d4-a716-446655440000");
    ASSERT_OK(uuid_format_braces(&uuid, buf, sizeof(buf)));
    ASSERT_STR_EQ(buf, "{550e8400-e29b-41d4-a716-446655440000}");
}

TEST(format_options_upper) {
    uuid_t uuid;
    char buf[UUID_STRING_LEN];
    uuid_parse(&uuid, "550e8400-e29b-41d4-a716-446655440000");
    ASSERT_OK(uuid_format_options(&uuid, buf, sizeof(buf), UUID_FMT_UPPER));
    ASSERT_STR_EQ(buf, "550E8400-E29B-41D4-A716-446655440000");
}

TEST(format_options_compact_upper) {
    uuid_t uuid;
    char buf[UUID_COMPACT_LEN];
    uuid_parse(&uuid, "550e8400-e29b-41d4-a716-446655440000");
    ASSERT_OK(uuid_format_options(&uuid, buf, sizeof(buf), UUID_FMT_COMPACT | UUID_FMT_UPPER));
    ASSERT_STR_EQ(buf, "550E8400E29B41D4A716446655440000");
}

TEST(format_options_braces) {
    uuid_t uuid;
    char buf[39];
    uuid_parse(&uuid, "550e8400-e29b-41d4-a716-446655440000");
    ASSERT_OK(uuid_format_options(&uuid, buf, sizeof(buf), UUID_FMT_BRACES));
    ASSERT_STR_EQ(buf, "{550e8400-e29b-41d4-a716-446655440000}");
}

TEST(format_binary) {
    uuid_t uuid;
    uint8_t buf[UUID_SIZE];
    uint8_t expected[16] = {0x55,0x0e,0x84,0x00,0xe2,0x9b,0x41,0xd4,
                           0xa7,0x16,0x44,0x66,0x55,0x44,0x00,0x00};
    uuid_parse(&uuid, "550e8400-e29b-41d4-a716-446655440000");
    ASSERT_OK(uuid_format_binary(&uuid, buf, sizeof(buf)));
    ASSERT(memcmp(buf, expected, 16) == 0);
}

TEST(format_buffer_too_small) {
    uuid_t uuid;
    char buf[10];
    uuid_parse(&uuid, "550e8400-e29b-41d4-a716-446655440000");
    ASSERT(uuid_format(&uuid, buf, sizeof(buf)) == UUID_E_BUFFER_TOO_SMALL);
}

TEST(format_to_string) {
    uuid_t uuid;
    char buf[UUID_STRING_LEN];
    uuid_parse(&uuid, "550e8400-e29b-41d4-a716-446655440000");
    ASSERT(uuid_to_string(&uuid, buf, sizeof(buf)) != NULL);
    ASSERT_STR_EQ(buf, "550e8400-e29b-41d4-a716-446655440000");
}

/* ── Round-trip Tests ──────────────────────────────────────────────────── */

TEST(roundtrip_canonical) {
    uuid_t a, b;
    char buf[UUID_STRING_LEN];
    uuid_v4(&a);
    uuid_format(&a, buf, sizeof(buf));
    uuid_parse(&b, buf);
    ASSERT(uuid_compare(&a, &b) == 0);
}

TEST(roundtrip_compact) {
    uuid_t a, b;
    char buf[UUID_COMPACT_LEN];
    uuid_v4(&a);
    uuid_format_compact(&a, buf, sizeof(buf));
    uuid_parse(&b, buf);
    ASSERT(uuid_compare(&a, &b) == 0);
}

TEST(roundtrip_binary) {
    uuid_t a, b;
    uint8_t buf[UUID_SIZE];
    uuid_v4(&a);
    uuid_format_binary(&a, buf, sizeof(buf));
    uuid_parse_binary(&b, buf, sizeof(buf));
    ASSERT(uuid_compare(&a, &b) == 0);
}

/* ── Comparison Tests ──────────────────────────────────────────────────── */

TEST(compare_equal) {
    uuid_t a, b;
    uuid_v4(&a);
    uuid_copy(&b, &a);
    ASSERT(uuid_compare(&a, &b) == 0);
}

TEST(compare_less) {
    uuid_t a, b;
    uuid_init_nil(&a);
    uuid_v4(&b);
    ASSERT(uuid_compare(&a, &b) < 0);
}

TEST(compare_greater) {
    uuid_t a, b;
    uuid_v4(&a);
    uuid_init_nil(&b);
    ASSERT(uuid_compare(&a, &b) > 0);
}

/* ── Sorting Tests ─────────────────────────────────────────────────────── */

TEST(sort_ascending) {
    uuid_t uuids[5];
    uuid_init_nil(&uuids[4]);
    uuid_init_max(&uuids[0]);
    uuid_v4(&uuids[1]);
    uuid_v4(&uuids[2]);
    uuid_v4(&uuids[3]);
    uuid_sort_asc(uuids, 5);
    ASSERT(uuid_is_nil(&uuids[0]));
    ASSERT(uuid_is_max(&uuids[4]));
}

TEST(sort_descending) {
    uuid_t uuids[5];
    uuid_init_nil(&uuids[0]);
    uuid_init_max(&uuids[4]);
    uuid_v4(&uuids[1]);
    uuid_v4(&uuids[2]);
    uuid_v4(&uuids[3]);
    uuid_sort_desc(uuids, 5);
    ASSERT(uuid_is_nil(&uuids[4]));
    ASSERT(uuid_is_max(&uuids[0]));
}

/* ── Hashing Tests ─────────────────────────────────────────────────────── */

TEST(hash_consistent) {
    uuid_t a, b;
    uuid_v4(&a);
    uuid_copy(&b, &a);
    ASSERT(uuid_hash(&a) == uuid_hash(&b));
}

TEST(hash_different) {
    uuid_t a, b;
    uuid_init_nil(&a);
    uuid_init_max(&b);
    ASSERT(uuid_hash(&a) != uuid_hash(&b));
}

/* ── Byte Access Tests ─────────────────────────────────────────────────── */

TEST(byte_at_valid) {
    uuid_t uuid;
    uint8_t byte;
    uuid_parse(&uuid, "550e8400-e29b-41d4-a716-446655440000");
    ASSERT_OK(uuid_byte_at(&uuid, 0, &byte));
    ASSERT_EQ(byte, 0x55);
}

TEST(byte_at_invalid) {
    uuid_t uuid;
    uint8_t byte;
    uuid_init_nil(&uuid);
    ASSERT(uuid_byte_at(&uuid, 16, &byte) != UUID_OK);
    ASSERT(uuid_byte_at(&uuid, 100, &byte) != UUID_OK);
}

TEST(bytes_pointer) {
    uuid_t uuid;
    const uint8_t *ptr;
    uuid_parse(&uuid, "550e8400-e29b-41d4-a716-446655440000");
    ptr = uuid_bytes(&uuid);
    ASSERT(ptr != NULL);
    ASSERT_EQ(ptr[0], 0x55);
}

/* ── Namespace Tests ───────────────────────────────────────────────────── */

TEST(namespace_dns) {
    uuid_t ns;
    static const uint8_t expected[16] = {
        0x6b,0xa7,0xb8,0x10,0x9d,0xad,0x11,0xd1,
        0x80,0xb4,0x00,0xc0,0x4f,0xd4,0x30,0xc8
    };
    ASSERT_OK(uuid_namespace(UUID_NS_DNS, &ns));
    ASSERT(memcmp(ns.bytes, expected, 16) == 0);
}

TEST(namespace_url) {
    uuid_t ns;
    ASSERT_OK(uuid_namespace(UUID_NS_URL, &ns));
}

TEST(namespace_oid) {
    uuid_t ns;
    ASSERT_OK(uuid_namespace(UUID_NS_OID, &ns));
}

TEST(namespace_x500) {
    uuid_t ns;
    ASSERT_OK(uuid_namespace(UUID_NS_X500, &ns));
}

TEST(namespace_invalid) {
    uuid_t ns;
    ASSERT(uuid_namespace((uuid_namespace_t)99, &ns) == UUID_E_NAMESPACE);
}

/* ── Version Info Tests ────────────────────────────────────────────────── */

TEST(version_string) {
    const char *v = uuid_version_string();
    ASSERT(v != NULL);
    ASSERT(strcmp(v, "0.1.0") == 0);
}

TEST(version_info) {
    int major, minor, patch;
    uuid_version_info(&major, &minor, &patch);
    ASSERT_EQ(major, 0);
    ASSERT_EQ(minor, 1);
    ASSERT_EQ(patch, 0);
}

/* ── Error Handling Tests ──────────────────────────────────────────────── */

TEST(strerror_ok) {
    ASSERT(strcmp(uuid_strerror(UUID_OK), "Success") == 0);
}

TEST(strerror_all_codes) {
    ASSERT(uuid_strerror(UUID_E_INVALID_ARG) != NULL);
    ASSERT(uuid_strerror(UUID_E_INVALID_UUID) != NULL);
    ASSERT(uuid_strerror(UUID_E_INVALID_FORMAT) != NULL);
    ASSERT(uuid_strerror(UUID_E_BUFFER_TOO_SMALL) != NULL);
    ASSERT(uuid_strerror(UUID_E_RANDOM) != NULL);
    ASSERT(uuid_strerror(UUID_E_OVERFLOW) != NULL);
}

TEST(null_checks) {
    uuid_t uuid;
    ASSERT(uuid_init_nil(NULL) != UUID_OK);
    ASSERT(uuid_init_max(NULL) != UUID_OK);
    ASSERT(uuid_copy(NULL, &uuid) != UUID_OK);
    ASSERT(uuid_copy(&uuid, NULL) != UUID_OK);
    ASSERT(uuid_compare(NULL, &uuid) == 0);
    ASSERT(uuid_is_nil(NULL) == 0);
    ASSERT(uuid_is_max(NULL) == 0);
    ASSERT(uuid_version(NULL) < 0);
    ASSERT(uuid_variant(NULL) < 0);
    ASSERT(uuid_hash(NULL) == 0);
}

/* ── Serialization Tests ───────────────────────────────────────────────── */

TEST(serialize_roundtrip) {
    uuid_t a, b;
    uint8_t buf[UUID_SIZE];
    uuid_v4(&a);
    ASSERT_OK(uuid_serialize(&a, buf, sizeof(buf)));
    ASSERT_OK(uuid_deserialize(&b, buf, sizeof(buf)));
    ASSERT(uuid_compare(&a, &b) == 0);
}

TEST(serialize_buffer_too_small) {
    uuid_t uuid;
    uint8_t buf[8];
    uuid_v4(&uuid);
    ASSERT(uuid_serialize(&uuid, buf, sizeof(buf)) == UUID_E_BUFFER_TOO_SMALL);
}

TEST(deserialize_buffer_too_small) {
    uuid_t uuid;
    uint8_t buf[8];
    ASSERT(uuid_deserialize(&uuid, buf, sizeof(buf)) == UUID_E_BUFFER_TOO_SMALL);
}

/* ── Swap Tests ────────────────────────────────────────────────────────── */

TEST(swap_uuids) {
    uuid_t a, b, orig_a, orig_b;
    uuid_v4(&a);
    uuid_v4(&b);
    uuid_copy(&orig_a, &a);
    uuid_copy(&orig_b, &b);
    ASSERT_OK(uuid_swap(&a, &b));
    ASSERT(uuid_compare(&a, &orig_b) == 0);
    ASSERT(uuid_compare(&b, &orig_a) == 0);
}

/* ── Set Tests ─────────────────────────────────────────────────────────── */

TEST(set_byte) {
    uuid_t uuid;
    int i;
    ASSERT_OK(uuid_set(&uuid, 0xAB));
    for (i = 0; i < 16; i++) {
        ASSERT_EQ(uuid.bytes[i], 0xAB);
    }
}

/* ── MD5 Tests ─────────────────────────────────────────────────────────── */

TEST(md5_empty) {
    uint8_t digest[16];
    /* MD5("") = d41d8cd98f00b204e9800998ecf8427e */
    uint8_t expected[16] = {0xd4,0x1d,0x8c,0xd9,0x8f,0x00,0xb2,0x04,
                           0xe9,0x80,0x09,0x98,0xec,0xf8,0x42,0x7e};
    uuid_md5("", 0, digest);
    ASSERT(memcmp(digest, expected, 16) == 0);
}

TEST(md5_abc) {
    uint8_t digest[16];
    /* MD5("abc") = 900150983cd24fb0d6963f7d28e17f72 */
    uint8_t expected[16] = {0x90,0x01,0x50,0x98,0x3c,0xd2,0x4f,0xb0,
                           0xd6,0x96,0x3f,0x7d,0x28,0xe1,0x7f,0x72};
    uuid_md5("abc", 3, digest);
    ASSERT(memcmp(digest, expected, 16) == 0);
}

/* ── SHA-1 Tests ───────────────────────────────────────────────────────── */

TEST(sha1_empty) {
    uint8_t digest[20];
    /* SHA1("") = da39a3ee5e6b4b0d3255bfef95601890afd80709 */
    uint8_t expected[20] = {0xda,0x39,0xa3,0xee,0x5e,0x6b,0x4b,0x0d,
                           0x32,0x55,0xbf,0xef,0x95,0x60,0x18,0x90,
                           0xaf,0xd8,0x07,0x09};
    uuid_sha1("", 0, digest);
    ASSERT(memcmp(digest, expected, 20) == 0);
}

TEST(sha1_abc) {
    uint8_t digest[20];
    /* SHA1("abc") = a9993e364706816aba3e25717850c26c9cd0d89d */
    uint8_t expected[20] = {0xa9,0x99,0x3e,0x36,0x47,0x06,0x81,0x6a,
                           0xba,0x3e,0x25,0x71,0x78,0x50,0xc2,0x6c,
                           0x9c,0xd0,0xd8,0x9d};
    uuid_sha1("abc", 3, digest);
    ASSERT(memcmp(digest, expected, 20) == 0);
}

/* ── Validate Tests ────────────────────────────────────────────────────── */

TEST(validate_valid) {
    ASSERT_OK(uuid_validate("550e8400-e29b-41d4-a716-446655440000"));
}

TEST(validate_compact) {
    ASSERT_OK(uuid_validate("550e8400e29b41d4a716446655440000"));
}

TEST(validate_invalid) {
    ASSERT(uuid_validate("not-a-uuid") != UUID_OK);
}

/* ── Extended Tests ──────────────────────────────────────────────────── */

TEST(v6_generate_convenience) {
    uuid_t a, b;
    ASSERT_OK(uuid_v6_generate(&a));
    ASSERT_OK(uuid_v6_generate(&b));
    ASSERT_EQ(uuid_version(&a), 6);
    ASSERT_EQ(uuid_variant(&a), UUID_VARIANT_RFC_4122);
    ASSERT(uuid_compare(&a, &b) != 0);
}

TEST(init_from_bytes) {
    uuid_t uuid;
    uint8_t bytes[16] = {0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,
                         0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10};
    ASSERT_OK(uuid_init_from_bytes(&uuid, bytes));
    ASSERT(uuid.bytes[0] == 0x01);
    ASSERT(uuid.bytes[15] == 0x10);
    ASSERT(memcmp(uuid.bytes, bytes, 16) == 0);
}

TEST(get_version_variant) {
    uuid_t uuid;
    uuid_version_t ver;
    uuid_variant_t var;
    uuid_v4(&uuid);
    ASSERT_OK(uuid_get_version(&uuid, &ver));
    ASSERT_EQ((int)ver, 4);
    ASSERT_OK(uuid_get_variant(&uuid, &var));
    ASSERT_EQ((int)var, UUID_VARIANT_RFC_4122);
}

TEST(last_error) {
    uuid_t uuid;
    const char *msg;
    uuid_init_nil(&uuid);
    msg = uuid_last_error();
    ASSERT(msg != NULL);
    ASSERT(strlen(msg) > 0);
}

TEST(v3_rfc_vector) {
    uuid_t ns, uuid;
    /* RFC 9562 Section D.3: UUIDv3 with DNS namespace */
    ASSERT_OK(uuid_namespace(UUID_NS_DNS, &ns));
    ASSERT_OK(uuid_v3(&ns, "www.example.com", 15, &uuid));
    ASSERT_EQ(uuid_version(&uuid), 3);
    ASSERT_EQ(uuid_variant(&uuid), UUID_VARIANT_RFC_4122);
    /* Deterministic: same input must produce same output */
    uuid_t uuid2;
    ASSERT_OK(uuid_v3(&ns, "www.example.com", 15, &uuid2));
    ASSERT(uuid_compare(&uuid, &uuid2) == 0);
    /* Different name must produce different UUID */
    ASSERT_OK(uuid_v3(&ns, "other.example.com", 18, &uuid2));
    ASSERT(uuid_compare(&uuid, &uuid2) != 0);
}

TEST(v5_rfc_vector) {
    uuid_t ns, uuid;
    /* RFC 9562 Section D.4: UUIDv5 with DNS namespace */
    ASSERT_OK(uuid_namespace(UUID_NS_DNS, &ns));
    ASSERT_OK(uuid_v5(&ns, "www.example.com", 15, &uuid));
    ASSERT_EQ(uuid_version(&uuid), 5);
    ASSERT_EQ(uuid_variant(&uuid), UUID_VARIANT_RFC_4122);
    /* Deterministic */
    uuid_t uuid2;
    ASSERT_OK(uuid_v5(&ns, "www.example.com", 15, &uuid2));
    ASSERT(uuid_compare(&uuid, &uuid2) == 0);
    /* v3 and v5 must differ for same input */
    uuid_t uuid3;
    ASSERT_OK(uuid_v3(&ns, "www.example.com", 15, &uuid3));
    ASSERT(uuid_compare(&uuid, &uuid3) != 0);
}

TEST(v1_generate_convenience) {
    uuid_t a, b;
    ASSERT_OK(uuid_v1_generate(&a));
    ASSERT_OK(uuid_v1_generate(&b));
    ASSERT_EQ(uuid_version(&a), 1);
    ASSERT_EQ(uuid_variant(&a), UUID_VARIANT_RFC_4122);
}

TEST(v7_generate_convenience) {
    uuid_t a, b;
    ASSERT_OK(uuid_v7_generate(&a));
    ASSERT_OK(uuid_v7_generate(&b));
    ASSERT_EQ(uuid_version(&a), 7);
    ASSERT_EQ(uuid_variant(&a), UUID_VARIANT_RFC_4122);
}

TEST(byte_at_edge) {
    uuid_t uuid;
    uint8_t byte;
    uuid_init_max(&uuid);
    ASSERT_OK(uuid_byte_at(&uuid, 0, &byte));
    ASSERT_EQ(byte, 0xFF);
    ASSERT_OK(uuid_byte_at(&uuid, 15, &byte));
    ASSERT_EQ(byte, 0xFF);
    uuid_init_nil(&uuid);
    ASSERT_OK(uuid_byte_at(&uuid, 0, &byte));
    ASSERT_EQ(byte, 0x00);
    ASSERT_OK(uuid_byte_at(&uuid, 15, &byte));
    ASSERT_EQ(byte, 0x00);
}

TEST(format_all_versions) {
    uuid_t uuid;
    char buf[UUID_STRING_LEN];
    int versions[] = {1, 3, 4, 5, 6, 7, 8};
    int i;
    for (i = 0; i < 7; i++) {
        uuid_v4(&uuid);
        uuid.bytes[6] = (uint8_t)((uuid.bytes[6] & 0x0F) | (versions[i] << 4));
        ASSERT_OK(uuid_format(&uuid, buf, sizeof(buf)));
        ASSERT(strlen(buf) == 36);
    }
}

TEST(parse_all_versions) {
    uuid_t uuid;
    const char *strs[] = {
        "550e8400-e29b-41d4-a716-446655440000",
        "550E8400E29B41D4A716446655440000",
        "550e8400e29b41d4a716446655440000",
        "{550e8400-e29b-41d4-a716-446655440000}"
    };
    int i;
    for (i = 0; i < 4; i++) {
        ASSERT_OK(uuid_parse(&uuid, strs[i]));
    }
}

TEST(serialize_all_versions) {
    uuid_t a, b;
    uint8_t buf[UUID_BINARY_SIZE];
    uuid_v4(&a);
    ASSERT_OK(uuid_serialize(&a, buf, sizeof(buf)));
    ASSERT_OK(uuid_deserialize(&b, buf, sizeof(buf)));
    ASSERT(uuid_compare(&a, &b) == 0);
}

TEST(concurrent_generation) {
    uuid_t uuids[10];
    int i, j;
    for (i = 0; i < 10; i++) {
        ASSERT_OK(uuid_v4(&uuids[i]));
    }
    for (i = 0; i < 10; i++) {
        for (j = i + 1; j < 10; j++) {
            ASSERT(uuid_compare(&uuids[i], &uuids[j]) != 0);
        }
    }
}

/* ── Main ──────────────────────────────────────────────────────────────── */

int main(void) {
    printf("uuid v%s - Test Suite\n", uuid_version_string());
    printf("========================================\n\n");

    printf("Basic Operations:\n");
    run_nil_init();
    run_nil_max();
    run_nil_format();
    run_max_format();
    run_set_byte();
    run_swap_uuids();
    printf("\n");

    printf("UUID v4 (Random):\n");
    run_v4_generation();
    run_v4_uniqueness();
    run_v4_format();
    run_v4_version_nibble();
    run_v4_variant_bits();
    run_v4_many_unique();
    printf("\n");

    printf("UUID v1 (Time-based):\n");
    run_v1_generation();
    run_v1_timestamp_extract();
    run_v1_clock_seq_extract();
    run_v1_node_extract();
    run_v1_monotonic();
    printf("\n");

    printf("UUID v6 (Reordered time):\n");
    run_v6_generation();
    run_v6_monotonic();
    printf("\n");

    printf("UUID v7 (Unix epoch time):\n");
    run_v7_generation();
    run_v7_timestamp_extract();
    run_v7_monotonic();
    run_v7_sortable();
    run_v7_many();
    printf("\n");

    printf("UUID v8 (Custom):\n");
    run_v8_generation();
    run_v8_custom_bytes();
    run_v8_custom_data_preserved();
    printf("\n");

    printf("UUID v3 (MD5 Name-based):\n");
    run_v3_generation();
    run_v3_deterministic();
    run_v3_different_names();
    run_v3_ns_dns();
    run_v3_ns_url();
    printf("\n");

    printf("UUID v5 (SHA-1 Name-based):\n");
    run_v5_generation();
    run_v5_deterministic();
    run_v5_different_from_v3();
    run_v5_ns_dns();
    printf("\n");

    printf("Parsing:\n");
    run_parse_canonical();
    run_parse_uppercase();
    run_parse_mixedcase();
    run_parse_compact();
    run_parse_braces();
    run_parse_nil();
    run_parse_max();
    run_parse_invalid_length();
    run_parse_invalid_chars();
    run_parse_empty();
    run_parse_trailing();
    run_parse_n_length();
    run_parse_binary();
    run_parse_binary_too_small();
    printf("\n");

    printf("Formatting:\n");
    run_format_canonical();
    run_format_compact();
    run_format_braces();
    run_format_options_upper();
    run_format_options_compact_upper();
    run_format_options_braces();
    run_format_binary();
    run_format_buffer_too_small();
    run_format_to_string();
    printf("\n");

    printf("Round-trip:\n");
    run_roundtrip_canonical();
    run_roundtrip_compact();
    run_roundtrip_binary();
    printf("\n");

    printf("Comparison & Sorting:\n");
    run_compare_equal();
    run_compare_less();
    run_compare_greater();
    run_sort_ascending();
    run_sort_descending();
    printf("\n");

    printf("Hashing:\n");
    run_hash_consistent();
    run_hash_different();
    printf("\n");

    printf("Byte Access:\n");
    run_byte_at_valid();
    run_byte_at_invalid();
    run_bytes_pointer();
    printf("\n");

    printf("Namespaces:\n");
    run_namespace_dns();
    run_namespace_url();
    run_namespace_oid();
    run_namespace_x500();
    run_namespace_invalid();
    printf("\n");

    printf("Version Info:\n");
    run_version_string();
    run_version_info();
    printf("\n");

    printf("Error Handling:\n");
    run_strerror_ok();
    run_strerror_all_codes();
    run_null_checks();
    printf("\n");

    printf("Serialization:\n");
    run_serialize_roundtrip();
    run_serialize_buffer_too_small();
    run_deserialize_buffer_too_small();
    printf("\n");

    printf("Crypto Primitives:\n");
    run_md5_empty();
    run_md5_abc();
    run_sha1_empty();
    run_sha1_abc();
    printf("\n");

    printf("Validation:\n");
    run_validate_valid();
    run_validate_compact();
    run_validate_invalid();
    printf("\n");

    printf("Extended Tests:\n");
    run_v6_generate_convenience();
    run_init_from_bytes();
    run_get_version_variant();
    run_last_error();
    run_v3_rfc_vector();
    run_v5_rfc_vector();
    run_v1_generate_convenience();
    run_v7_generate_convenience();
    run_byte_at_edge();
    run_format_all_versions();
    run_parse_all_versions();
    run_serialize_all_versions();
    run_concurrent_generation();
    printf("\n");

    printf("========================================\n");
    printf("Results: %d/%d passed", tests_passed, tests_run);
    if (tests_failed > 0) {
        printf(", %d FAILED", tests_failed);
    }
    printf("\n");

    return tests_failed > 0 ? 1 : 0;
}
