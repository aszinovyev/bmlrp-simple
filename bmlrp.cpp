#include <vector>
#include <set>
#include <tuple>
#include "bmlrp.h"
#include "misc.h"

Graph::Graph() {
    n = 0;
}

Graph::Graph(int n) {
    Graph::n = n;
    ids.resize(n);
}


bool SameColor(Addr a, Addr b, char level) {
    return ~((a ^ b) << level) & FirstBit;
}

Graph GOut(const int to, const Graph& gprime) {
    const int& n = gprime.n;

    int adjmat
}

// cl == current level
// nl == next level
Graph NextLevel(const Graph& clGraph, int cl, const vector<Addr>& addrs) {
    const int& n = clGraph.n;

    Graph g_out[n][n];

    bool changed = true;
    while (changed) {
        changed = false;

        for (int i = 0; i < n; ++i) {
            for (auto it = clGraph.edges.lower_bound(make_pair(i, 0));
                 it != clGraph.edges.end() && it->first == i; ++it)
            {
                const int j = it->second;

                Graph gprime;
                gprime.n = clGraph.n;
                gprime.ids = clGraph.ids;
                for (auto it = clGraph.edges.lower_bound(make_pair(i, 0));
                     it != clGraph.edges.end() && it->first == i; ++it)
                {
                    const int k = it->second;
                    if (k != j) {
                        gprime.edges.insert(g_out[k][i].edges.cbegin(), g_out[k][i].edges.cend());
                    }
                }

                Graph new_g_out = GOut(j, gprime);    // [i][j]
            }
        }
    }
}





