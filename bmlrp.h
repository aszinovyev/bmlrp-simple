#ifndef BMLRP_H
#define BMLRP_H

using namespace std;

typedef unsigned int Addr;

const Addr FirstBit = (Addr(-1) >> 1) + 1;

class Graph {
public:
    int n;
    set< pair<int, int> > edges;
    vector<int> ids;

    Graph();
    Graph(int n);
};

//bool SameColor(Addr a, Addr b, char level);

#endif // BMLRP_H
