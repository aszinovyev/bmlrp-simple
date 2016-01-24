#ifndef GRAPH_H
#define GRAPH_H

using namespace std;

class Graph {
public:
    uint n;
    vector< std::vector<uint> > edges;

    Graph();
    Graph(uint n);

    void Print();
};

#endif // GRAPH_H
