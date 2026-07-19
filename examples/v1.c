/*
 * v1.c - UUID v1 (time-based) example
 * Copyright (c) 2026 Muhammad Fiaz - MIT License
 */

#include <uuid/uuid.h>
#include <stdio.h>

int main(void) {
    uuid_v1_state_t state;
    uuid_t uuid;
    char buf[UUID_STRING_LEN];
    uint64_t timestamp;
    uint16_t clock_seq;
    uint8_t node[6];

    printf("uuid v%s - UUID v1 (Time-based) Example\n\n", uuid_version_string());

    /* Initialize state */
    uuid_v1_init(&state);
    printf("V1 state initialized\n");

    /* Generate UUID v1 */
    uuid_v1(&state, &uuid);
    uuid_format(&uuid, buf, sizeof(buf));
    printf("Generated v1:    %s\n", buf);
    printf("Version:         %d\n", uuid_version(&uuid));

    /* Extract timestamp */
    uuid_v1_timestamp(&uuid, &timestamp);
    printf("Timestamp:       %llu (100-ns intervals since Gregorian epoch)\n",
           (unsigned long long)timestamp);

    /* Extract clock sequence */
    uuid_v1_clock_seq(&uuid, &clock_seq);
    printf("Clock sequence:  %u\n", clock_seq);

    /* Extract node */
    uuid_v1_node(&uuid, node);
    printf("Node:            %02x:%02x:%02x:%02x:%02x:%02x\n",
           node[0], node[1], node[2], node[3], node[4], node[5]);

    return 0;
}
