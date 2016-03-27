#ifndef BMLRP_H
#define BMLRP_H

using namespace std;

typedef unsigned long long Addr;
const Addr FirstBit = ((Addr)-1 >> 1) + 1;

Graph NextLevel(const Graph& clGraph, const vector<Addr>& addrs);
Graph GetLevel(const Graph& level0, const vector<Addr>& addrs, uint level);

#endif // BMLRP_H
