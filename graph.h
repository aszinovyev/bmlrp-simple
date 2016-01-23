#ifndef GRAPH_H
#define GRAPH_H

using namespace std;

class Graph {
public:
    int n;
    vector< std::vector<int> > edges;

    Graph();
    Graph(int n);
};

#endif // GRAPH_H
