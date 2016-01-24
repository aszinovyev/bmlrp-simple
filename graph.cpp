#include "stable.h"
#include "graph.h"
#include "bmlrp.h"
#include "misc.h"

Graph::Graph() {
    n = 0;
}

Graph::Graph(uint n) {
    Graph::n = n;
    edges.resize(n);
}

void Graph::Print() {
    cout << n << " vertices" << endl;

    for (uint i = 0; i < n; ++i) {
        cout << i << " :  ";

        for (uint j = 0; j < edges[i].size(); ++j) {
            const uint to = edges[i][j];
            cout << to << " ";
        }

        cout << endl;
    }

    cout << endl;
}

//void Graph::addEdge(uint a, uint b) {
//    assert(a < n);
//    assert(b < n);

//    edges.insert( make_pair(a, b) );
//    edges.insert( make_pair(b, a) );
//}
