#ifndef BMLRP_H_
#define BMLRP_H_

#include <vector>

#include "graph.h"

typedef unsigned long long Addr;  // NOLINT

extern const Addr Msb;

Graph NextLevel(const Graph& clGraph, const std::vector<Addr>& addrs);
Graph GetLevel(const Graph& level0, const std::vector<Addr>& addrs, int level);

#endif  // BMLRP_H_
