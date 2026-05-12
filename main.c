#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int main(){
    
    long long start = millis()
    long long timestamp_ms;
    
    RingBuf rb;
    Entry entry;
    Entry out;

    rb_init(8);
    
    // generating 30 random temperature readings
    float reading[30];
    srand(time(NULL));
    
    for (int i = 0; i < 30; i++){
        reading[i] = rand() % (40 - 20 + 1) + 20;
        timestamp_ms = millis() - start;
        
        if (!rb_full(&rb)){
            rb_push(&rb, reading[i], timestamp_ms)
        }
        else{
            rb_avg(&rb);
            rb_pop(&rb, &out);
            rb_push(&rb, reading[i], timestamp_ms)
        }   
        
    }



    return 0;
}