#ifndef DEBUG_H_
#define DEBUG_H_

#include <iostream>

#include "bmlrp.h"
#include "graph.h"
#include "misc.h"

#define myassert(expr) { \
  if (!(expr)) { \
    std::cerr << __FILE__ << ":" << __LINE__ << ": " << __PRETTY_FUNCTION__ \
              << ": Assertion `" << __STRING(expr) \
              << "' failed." << std::endl; \
    throw(0); \
  } \
}

std::string AddrToString(Addr a, uchar n = sizeof(Addr) * 8,
                         bool format = true);

void PrintGraph(const Graph& g);

#endif  // DEBUG_H_
