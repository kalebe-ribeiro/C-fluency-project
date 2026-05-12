#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ring_buf.h"

RingBuf rb_init(size_t capacity){
    RingBuf rb;

    rb.capacity = capacity;
    rb.buf = malloc(capacity * sizeof(Entry));
    if (rb.buf == NULL){
        printf("Could'nt allocate memory.");
    }

    rb.head = 0;
    rb.tail = 0;
    rb.count = 0;

    return rb;
}

bool rb_push(RingBuf *rb, float value, long long timestamp_ms){
    Entry entry;

    entry.value = value;
    entry.timestamp_ms = timestamp_ms;

    rb->buf[rb->head] = entry; 

    rb->head = (rb->head + 1) % rb->capacity; 
    if (rb->count < rb->capacity){
        rb->count += 1;
    }

    return 1;
}

bool rb_pop(RingBuf *rb, Entry *out){
    if (rb->count == 0){
        return 0;
    }

    *out = rb->buf[rb->tail]; 

    rb->tail = (rb->tail + 1) % rb->capacity;
    rb->count -= 1;

    return 1;
}

bool rb_peek(const RingBuf *rb, Entry *out){
    if (rb->count == 0){
        return 0;
    }
    
    *out = rb->buf[rb->tail];

    return 1;
}

size_t rb_count(const RingBuf *rb){
    return rb->count;
}

bool rb_full(const RingBuf *rb){
    if (rb->count != rb->capacity){
        return 0;
    }

    return 1;
}

void rb_free(RingBuf *rb){
    free(rb->buf);
    rb->buf = NULL;
}

float rb_avg(RingBuf *rb){
    float sum = 0;
    float avg;

    for (int i = 0; i != rb->count; i++){   

        sum += rb->buf[(rb->tail + i) % rb->capacity].value;
    }

    avg = sum/rb->count;

    return avg;
}

long long millis() {
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);

    return (long long)ts.tv_sec * 1000 +
           ts.tv_nsec / 1000000;
}