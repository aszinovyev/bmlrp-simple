#include <vector>
#include "graph.h"

Graph::Graph() {
    n = 0;
}

Graph::Graph(int n) {
    Graph::n = n;
    edges = vector< vector<int> >(n);
}
