#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "ring_buf.h"

int main(){
    
    double start = millis();
    double timestamp_ms;
    
    RingBuf rb;
    Entry out;

    rb = rb_init(2);
    if (rb.buf == NULL){
        return 1;
    }
    
    // generating 30 random temperature readings
    float reading[30];
    srand(time(NULL));
    
    for (size_t i = 0; i < 30; i++){
        reading[i] = rand() % (85 - (-10) + 1) + (-10);
        timestamp_ms = millis() - start;
        
        if (!rb_full(&rb)){
            rb_push(&rb, reading[i], timestamp_ms);
        }
        else{
            printf("Average buffer temperature: %f\n", rb_avg(&rb));
            rb_pop(&rb, &out);
            rb_push(&rb, reading[i], timestamp_ms);
        }   
        
        rb_dump_csv(&rb);
    }

    rb_free(&rb);

    return 0;
}