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


void Graph::AddDirEdge(uint a, uint b) {
    assert(a < n);
    assert(b < n);

    edges[a].push_back(b);
}

void Graph::AddEdge(uint a, uint b) {
    assert(a < n);
    assert(b < n);

    edges[a].push_back(b);
    edges[b].push_back(a);
}

void Graph::Simplify() {
    for (uint i = 0; i < n; ++i) {
        sort(edges[i].begin(), edges[i].end());

        auto tail = unique(edges[i].begin(), edges[i].end());
        edges[i].resize( distance(edges[i].begin(), tail) );
    }
}

bool Graph::Connected(uint a, uint b) const {
    return ( find(edges[a].cbegin(), edges[a].cend(), b) != edges[a].cend() );
}


void Graph::Print() const {
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
