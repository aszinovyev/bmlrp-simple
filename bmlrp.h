#ifndef BMLRP_H
#define BMLRP_H

using namespace std;

typedef unsigned int Addr;

class Graph {
public:
    int n;
    vector< std::vector<int> > edges;
    vector<int> ids;

    Graph();
    Graph(int n);
};

#endif // BMLRP_H
