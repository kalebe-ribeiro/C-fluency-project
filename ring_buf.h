#pragma once
#include <stdbool.h>
#include <stdint.h>

typedef struct{
    float value;
    uint32_t timestamp_ms;
} Entry;

typedef struct{
    Entry *buf;
    size_t head;
    size_t tail;
    size_t count;
    size_t capacity;
} RingBuf;

RingBuf rb_init(size_t capacity);

bool rb_push(RingBuf *rb, float value, uint32_t timestamp_ms);
bool rb_pop(RingBuf *rb, Entry *out);
bool rb_peek(const RingBuf *rb, Entry *out);
size_t rb_count(const RingBuf *rb);
bool rb_full(const RingBuf *rb);
void rb_free(RingBuf *rb);
float rb_avg(RingBuf *rb);

long millis();