#ifndef MISC_H_
#define MISC_H_

#include <random>
#include <sys/resource.h>

typedef unsigned int uint;
typedef unsigned char uchar;

extern std::default_random_engine Gen;

void set_stack_size(rlim_t size);

#endif  // MISC_H_
