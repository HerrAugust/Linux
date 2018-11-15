#ifndef SCHED_DEADLINE_H
#define SCHED_DEADLINE_H

#define _GNU_SOURCE
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/sched.h>
#include <unistd.h>
#include <time.h>
#include <sched.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <sys/types.h>

#define gettid() syscall(__NR_gettid)

#define SCHED_DEADLINE		6
#define SCHED_FLAG_RESET_ON_FORK 0x01

 /* XXX use the proper syscall numbers */
 #ifdef __x86_64__
 #define __NR_sched_setattr		314
 #define __NR_sched_getattr		315
 #endif

 #ifdef __i386__
 #define __NR_sched_setattr		351
 #define __NR_sched_getattr		352
 #endif

 #ifdef __arm__
 #define __NR_sched_setattr		380
 #define __NR_sched_getattr		381
 #endif

struct sched_attr {
	__u32 size;

	__u32 sched_policy;
	__u64 sched_flags;

	/* SCHED_NORMAL, SCHED_BATCH */
	__s32 sched_nice;

	/* SCHED_FIFO, SCHED_RR */
	__u32 sched_priority;

	/* SCHED_DEADLINE (nsec) */
	__u64 sched_runtime;
	__u64 sched_deadline;
	__u64 sched_period;
 };

// public functions:
void setSCHED_DL( unsigned long wcet, unsigned long deadline, unsigned long period );

pthread_t getThreadID();

#endif // SCHED_DEADLINE_H
