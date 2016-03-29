#ifndef MYASSERT_H
#define MYASSERT_H

#define myassert(expr) { \
    if(!(expr)) { \
        std::cerr << __FILE__ << ":" << __LINE__ << ": " << __PRETTY_FUNCTION__ \
                  << ": Assertion `" << __STRING(expr) << "' failed." << std::endl; \
        throw(0); \
    } \
}

string Binary(Addr a, uchar n = sizeof(Addr) * 8, bool format = true);

void PrintGraph(const Graph& g);

#endif // MYASSERT_H
