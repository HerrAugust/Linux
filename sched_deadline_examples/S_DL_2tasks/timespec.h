#ifndef __TIMESPEC_H__
#define __TIMESPEC_H__

#include <time.h>

static inline long unsigned timespec_sub_us(struct timespec ts1, struct timespec ts2) {
  return (ts1.tv_sec - ts2.tv_sec) * 1000000 + (ts1.tv_nsec - ts2.tv_nsec) / 1000;
}

static inline struct timespec timespec_add_us(struct timespec ts, unsigned long us) {
  ts.tv_nsec += us * 1000;
  while (ts.tv_nsec >= 1000000000l) {
    ts.tv_sec++;
    ts.tv_nsec -= 1000000000l;
  }
  return ts;
}

static inline struct timespec timespec_add(struct timespec a, struct timespec b) {
  struct timespec c;
  c.tv_sec = a.tv_sec + b.tv_sec;
  c.tv_nsec = a.tv_nsec + b.tv_nsec;
  while (c.tv_nsec >= 1000000000l) {
    c.tv_sec++;
    c.tv_nsec -= 1000000000l;
  }
  return c;
}

static inline struct timespec timespec_sub(struct timespec a, struct timespec b) {
  struct timespec c;
  c.tv_sec = a.tv_sec - b.tv_sec;
  c.tv_nsec = a.tv_nsec - b.tv_nsec;
  while (c.tv_nsec < 0) {
    c.tv_sec--;
    c.tv_nsec += 1000000000l;
  }
  return c;
}

static inline int timespec_leq(struct timespec a, struct timespec b) {
  return (a.tv_sec < b.tv_sec
	  || (a.tv_sec == b.tv_sec && (signed long) a.tv_nsec - b.tv_nsec < 0));
}

#endif
