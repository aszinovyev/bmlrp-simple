#include "stable.h"
#include "myassert.h"
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
    myassert(a < n);
    myassert(b < n);

    edges[a].push_back(b);
}

void Graph::AddEdge(uint a, uint b) {
    myassert(a < n);
    myassert(b < n);

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

bool Graph::Symmetric() const {
    for (uint i = 0; i < n; ++i) {
        for (uint j = 0; j < edges[i].size(); ++j) {
            const uint to = edges[i][j];

            if (!Connected(to, i)) {
                return false;
            }
        }
    }

    return true;
}

void Graph::Print() const {
    cout << n << " vertices:  ";

    for (uint i = 0; i < n; ++i) {
        for (uint j = 0; j < edges[i].size(); ++j) {
            const uint to = edges[i][j];
            cout << i << "-" << to << " ";
        }
    }

    cout << endl;
}
