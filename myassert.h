#ifndef MYASSERT_H
#define MYASSERT_H

#define myassert(expr) { \
    if(!(expr)) { \
        std::cerr << __FILE__ << ":" << __LINE__ << ": " << __PRETTY_FUNCTION__ \
                  << ": Assertion `" << __STRING(expr) << "' failed." << std::endl; \
        throw(0); \
    } \
}

#endif // MYASSERT_H
