/**
  * SCHED_DEADLINE task with C = 50ms every D = T = 1000ms = 1 sec.
  * Program must run with sudo ./main on Linux 3.14+
  *
  * Contributions:
  * Agostino Mascitti - original author, Nov. 2018
  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include <pthread.h>

// #include <assert.h>

#include "SCHED_DEADLINE.h"

int main(int argc, char** argv) {
    unsigned int period     = 1 * 1000 * 1000; // us
    unsigned int wcet       = 50 * 1000 * 1000; // us. Commonly it is WCET + 20% to prevent overrunning situations
    unsigned int deadline   = 1 * 1000 * 1000; // us
    unsigned long flags     = 0;

    while(argc > 0) {
        if(strcmp(*argv, "-h") == 0 || strcmp(*argv, "-help") == 0)
            printf("SCHED_DEADLINE task with C = 50ms every D = T = 1000ms = 1\n");
        argc--;
    }    
 
    // with SCHED_DEADLINE one must set WCET, period and deadline
    struct sched_attr attr = {
        .size = sizeof(struct sched_attr),
        .sched_policy = SCHED_DEADLINE,
        .sched_flags = flags,
        .sched_runtime  = wcet,
        .sched_deadline = deadline,
        .sched_period   = period
    };

    printf("Calling sched_setattr(): runtime=%llu, deadline=%llu, period=%llu, flags=%llu\n",
	 attr.sched_runtime, attr.sched_deadline, attr.sched_period, attr.sched_flags);
    if (sched_setattr(0, &attr, 0) < 0) {
        perror("setattr() failed");
        exit(-1);
    }
    
    // here is the SCHED_DEADLINE process code
    printf("Here the SCHED_DEADLINE task code begins\n");
    
    return 0;

}
