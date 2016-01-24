#ifndef BMLRP_H
#define BMLRP_H

using namespace std;

typedef uint Addr;
const Addr FirstBit = ((Addr)-1 >> 1) + 1;

Graph NextLevel(const Graph& clGraph, const vector<Addr>& addrs);

#endif // BMLRP_H
