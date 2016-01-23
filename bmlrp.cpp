#include <vector>
#include "bmlrp.h"

Graph::Graph() {
    n = 0;
}

Graph::Graph(int n) {
    Graph::n = n;
    edges.resize(n);
    ids.resize(n);
}
