/**
  * 2 SCHED_DEADLINE threads that simulate their work with sleep. 50ms every 100ms and 20ms every 80ms (U=3/4 <= 1) 
  * Program must run with sudo ./main on Linux 3.14+
  *
  * Contributions:
  * Agostino Mascitti - original author, Nov. 2018
  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#include "SCHED_DEADLINE.h"
#include "timespec.h"

#define THREAD_COUNT 2

// read-only parameters
unsigned long wcet_us[2]       = {  50 * 1000 * 1000, 20 * 1000 * 1000 }; // 50ms & 20ms. Commonly it is actual WCET + 20% to prevent overrunning situations
unsigned long period_us[2]     = { 160 * 1000 * 1000, 80 * 1000 * 1000 }; // us
unsigned long deadline_us[2]   = { 160 * 1000 * 1000, 80 * 1000 * 1000 }; // us

// --------------------------------------------------------

// Function executed by threads
void* threadFunc(void* args) {
    pthread_t tid = getThreadID();
    int index = *((int*) args);
    unsigned int div = 1000 * 1000;
    struct timespec ts_start, ts_next, ts_end;
    
    // In SCHED_DEADLINE, father doesn't know its children's TID, thus they set scheduling class & params by themselves.
    setSCHED_DL(wcet_us[index], deadline_us[index], period_us[index]);

    // code for sleeping
    clock_gettime(CLOCK_MONOTONIC, &ts_start);
    ts_next = ts_start;

    while(1) {
        clock_gettime(CLOCK_MONOTONIC, &ts_start);
        
        // simulate pthread job: sleep
        printf("Pthread TID=%ld sleeping for %lu ms every %lu. Time = %ldms\n", tid, wcet_us[index] / div, period_us[index] / div, ts_start.tv_nsec / 1000000);
        timespec_add_us(ts_next, wcet_us[index]);
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &ts_next, NULL);

        clock_gettime(CLOCK_MONOTONIC, &ts_end);
        printf("Pthread TID=%ld elapsed %ldus\n", tid, timespec_sub_us(ts_end, ts_start));
        
        sched_yield(); // thread is descheduled. See you at the beginning of next period!
    }

    return NULL;
}

int main(int argc, char** argv) { 
    while(argc > 0) {
        if(strcmp(*argv, "-h") == 0 || strcmp(*argv, "-help") == 0) {
            printf("2 SCHED_DEADLINE pthreads example: 50ms every 100ms and 20ms every 80ms (U=3/4 <= 1)\n");
            return 0;
        }
        argc--;
    }

    // create 2 threads	
    pthread_t t1, t2;
    int index0 = 0; int index1 = 1;
    pthread_create(&t1, NULL, threadFunc, &index0);
    pthread_create(&t2, NULL, threadFunc, &index1);
    
    sleep(5); // sec

    return 0;

}
