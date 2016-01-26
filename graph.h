#ifndef GRAPH_H
#define GRAPH_H

using namespace std;

class Graph {
public:
    uint n;
    vector< std::vector<uint> > edges;

    Graph();
    Graph(uint n);

    void AddDirEdge(uint a, uint b);
    void AddEdge(uint a, uint b);
    void Simplify();

    bool Connected(uint a, uint b) const;
    bool Symmetric() const;

    void Print() const;
};

#endif // GRAPH_H
