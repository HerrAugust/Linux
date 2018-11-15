#include "SCHED_DEADLINE.h"

int sched_setattr(pid_t pid,
              const struct sched_attr *attr,
              unsigned int flags)
{
    return syscall(__NR_sched_setattr, pid, attr, flags);
}

int sched_getattr(pid_t pid,
              struct sched_attr *attr,
              unsigned int size,
              unsigned int flags)
{
    return syscall(__NR_sched_getattr, pid, attr, size, flags);
}

/**
  * Return ID of thread (TID) under SCHED_DEADLINE
  */ 
pthread_t getThreadID() {
    return gettid();
}

/**
  * Creates a SCHED_DEADLINE task and executes its function.
  * Each such task has period, WCET and deadline. Measures in nsec.
  * Remember WCET must be slightly greater than its actual WCET (say +20%) 
  */
void setSCHED_DL( unsigned long wcet, unsigned long deadline, unsigned long period ) {
    unsigned long flags = 0;
    pthread_t pid = getThreadID();

    // with SCHED_DEADLINE one must set WCET, period and deadline
    struct sched_attr attr = {
        .size = sizeof(struct sched_attr),
        .sched_policy = SCHED_DEADLINE,
        .sched_flags = flags,
        .sched_runtime  = wcet,
        .sched_deadline = deadline,
        .sched_period   = period
    };

    printf("Calling sched_setattr(): tid=%lu, runtime=%llu ms, deadline=%llu ms, period=%llu ms flags=%llu\n",
	    pid, attr.sched_runtime, attr.sched_deadline, attr.sched_period, attr.sched_flags);
    if (sched_setattr(pid, &attr, 0) < 0) {
        perror("setattr() failed");
        exit(-1);
    }

}
