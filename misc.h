#ifndef MISC_H
#define MISC_H

typedef unsigned int uint;
typedef unsigned char uchar;

extern std::default_random_engine Gen;

void set_stack_size(rlim_t size);

#endif // MISC_H
