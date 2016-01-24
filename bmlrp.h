#ifndef BMLRP_H
#define BMLRP_H

using namespace std;

typedef uint Addr;

const Addr FirstBit = ((Addr)-1 >> 1) + 1;

class Graph {
public:
    uint n;
    set< pair<uint, uint> > edges;

    Graph();
    Graph(uint n);

    void addEdge(uint a, uint b);

    void merge(const Graph& g);
    void isolate(uint node);

    bool equals(const Graph& g);
};

//bool SameColor(Addr a, Addr b, char level);

#endif // BMLRP_H
