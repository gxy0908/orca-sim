#include <hellfire.h>
#include <noc.h>

#include "producer-consumer.h"

void consumer(void)
{
    int8_t buf[500];
    uint16_t cpu, port, size, counter;
    int16_t val;

    if (hf_comm_create(hf_selfid(), 5000, 0)){
        panic(0xff);
    }

    counter = 0;
	
    while (1){
	
        int32_t i = hf_recvprobe();
	
        if(i >= 0){

            val = hf_recv(&cpu, &port, buf, &size, i);
	
            if (val){
		printf("hf_recv(): error %d\n", val);
            } else {		
	        printf("cpu %d, port %d, ch %d, size %d, #%d [free queue: %d]\n",
                    cpu, port, i, size, counter, hf_queue_count(pktdrv_queue));
                counter++;
	    }
	}
    }
}
