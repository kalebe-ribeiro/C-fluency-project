#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "ring_buf.h"

int main(){
    int reading_size;
    int buf_size;
    
    RingBuf rb;
    Entry out;

    printf("Enter the number of readings: ");
    scanf("%d", &reading_size);

    printf("Enter the buffer size: ");
    scanf("%d", &buf_size);

    rb = rb_init(buf_size);
    if (rb.buf == NULL){
        return 1;
    }
    
    // generating n random temperature readings
    float reading[reading_size];
    srand(time(NULL));

    double start = millis();
    double timestamp_ms;
    
    for (int i = 0; i < reading_size; i++){
        reading[i] = rand() % (85 - (-10) + 1) + (-10);
        timestamp_ms = millis() - start;
        
        if (!rb_full(&rb)){
            rb_push(&rb, reading[i], timestamp_ms);
            printf("Average buffer temperature: %.2f\n", rb_avg(&rb));
        }
        else{
            printf("Average buffer temperature: %.2f\n", rb_avg(&rb));
            rb_pop(&rb, &out);
            rb_push(&rb, reading[i], timestamp_ms);
        }   
        
        rb_dump_csv(&rb);
    }

    rb_free(&rb);

    return 0;
}