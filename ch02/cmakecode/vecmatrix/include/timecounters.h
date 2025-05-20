

#ifndef __TIMERCOUNTERS_H__
#define __TIMERCOUNTERS_H__
#include <sys/time.h>
inline int64_t GetUsec() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000000l) + tv.tv_usec;
}

#endif
