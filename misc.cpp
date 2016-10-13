#include "stable.h"
#include "debug.h"
#include "misc.h"

std::default_random_engine Gen(0xABCD2345);

void set_stack_size(rlim_t size) {
    struct rlimit rl;
    myassert(getrlimit(RLIMIT_STACK, &rl) == 0);

    if (rl.rlim_cur < size) {
        rl.rlim_cur = size;
        myassert(setrlimit(RLIMIT_STACK, &rl) == 0);
    }
}
