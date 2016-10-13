#ifndef BMLRP_H
#define BMLRP_H

typedef unsigned long long Addr;

extern const Addr Msb;

Graph NextLevel(const Graph& clGraph, const std::vector<Addr>& addrs);
Graph GetLevel(const Graph& level0, const std::vector<Addr>& addrs, int level);

#endif // BMLRP_H
