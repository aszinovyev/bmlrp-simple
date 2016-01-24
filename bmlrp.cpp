#include <iostream>
#include <cassert>
#include <memory.h>

#include <algorithm>
#include <vector>
#include <set>
#include <tuple>

#include "bmlrp.h"
#include "misc.h"

Graph::Graph() {
    n = 0;
}

Graph::Graph(uint n) {
    Graph::n = n;
}

void Graph::addEdge(uint a, uint b) {
    assert(a < n);
    assert(b < n);

    edges.insert( make_pair(a, b) );
    edges.insert( make_pair(b, a) );
}

void Graph::merge(const Graph& g) {
    assert(n == g.n);

    for (auto it = g.edges.cbegin(); it != g.edges.cend(); ++it) {
        uint a = it->first;
        uint b = it->second;

        edges.insert( make_pair(a, b) );
        edges.insert( make_pair(b, a) );
    }
}

void Graph::isolate(uint node) {
    assert(node < n);

    for (auto it = edges.lower_bound(make_pair(node, 0)); it != edges.end() && it->first == node; ++it) {
        uint a = it->first;
        uint b = it->second;

        edges.erase( make_pair(b, a) );
        it = edges.erase(it);
    }
}

bool Graph::equals(const Graph &g) {
    return (g.n == n) && (g.edges == edges);
}

bool DiffColor(Addr a, Addr b) {
    return (a ^ b) & FirstBit;
}

Graph GOut(const uint a, const uint b, const Graph& g, const Graph& gprime, const vector<Addr>& addrs) {
    const uint Inf = (uint)-1 >> 1;

    const uint n = gprime.n;

    uint dist_g[n][n];
    uint dist_gprime[n][n];
    uint next_gprime[n][n];
    memset(next_gprime, 0xff, sizeof(next_gprime));

    for (uint i = 0; i < n; ++i) {
        for (uint j = 0; j < n; ++j) {
            dist_g[i][j] = Inf;
            dist_gprime[i][j] = Inf;
        }
        dist_g[i][i] = 0;
        dist_gprime[i][i] = 0;
        next_gprime[i][i] = i;
    }
    for (auto it = g.edges.cbegin(); it != g.edges.cend(); ++it) {
        uint a = it->first;
        uint b = it->second;

        dist_g[a][b] = 1;
    }
    for (auto it = gprime.edges.cbegin(); it != gprime.edges.cend(); ++it) {
        uint a = it->first;
        uint b = it->second;

        dist_gprime[a][b] = 1;
        next_gprime[a][b] = b;
    }

    for (uint k = 0; k < n; ++k) {
        for (uint i = 0; i < n; ++i) {
            for (uint j = 0; j < n; ++j)
            {
                if (dist_g[i][k] + dist_g[k][j] < dist_g[i][j]) {
                    dist_g[i][j] = dist_g[i][k] + dist_g[k][j];
                }
                if (dist_gprime[i][k] + dist_gprime[k][j] < dist_gprime[i][j]) {
                    dist_gprime[i][j] = dist_gprime[i][k] + dist_gprime[k][j];
                    next_gprime[i][j] = next_gprime[i][k];
                }
            }
        }
    }


    Graph res;

    for (uint i = 0; i < n; ++i) {
        if (DiffColor(addrs[a], addrs[i]) && (i != b) && (dist_g[a][i] != Inf)) {
            bool add_node_i = true;

            for (uint j = 0; j < n; ++i) {
                if (DiffColor(addrs[a], addrs[j])) {
                    if ((dist_g[i][j] < dist_gprime[i][b]) && (dist_g[j][b] < dist_gprime[i][b])) {
                        add_node_i = false;
                    }
                }
            }

            if (add_node_i) {
                uint node = a;
                do {
                    uint next = next_gprime[node][i];
                    res.addEdge(node, next);

                    node = next;
                } while (node != i);
            }
        }
    }

    return res;
}

// cl == current level
Graph NextLevel(const Graph& clGraph, const vector<Addr>& addrs) {
    const uint n = clGraph.n;

    Graph g_out[n][n];

    bool changed;
    do {
        changed = false;

        for (uint i = 0; i < n; ++i) {
            // building i's graph G
            Graph g;
            g.n = clGraph.n;
            for (auto it = clGraph.edges.lower_bound(make_pair(i, 0));
                 it != clGraph.edges.end() && it->first == i; ++it)
            {
                const uint j = it->second;

                g.merge( g_out[j][i] );
                g.addEdge(i, j);
            }

            for (auto it = clGraph.edges.lower_bound(make_pair(i, 0));
                 it != clGraph.edges.end() && it->first == i; ++it)
            {
                const uint j = it->second;

                Graph gprime;
                gprime.n = clGraph.n;
                for (auto it = clGraph.edges.lower_bound(make_pair(i, 0));
                     it != clGraph.edges.end() && it->first == i; ++it)
                {
                    const uint k = it->second;
                    if (k != j) {
                        gprime.merge( g_out[k][i] );
                        gprime.addEdge(i, k);
                    }
                }
                gprime.addEdge(i, j);

                Graph new_g_out = GOut(i, j, g, gprime, addrs);    // [i][j]

                if (!new_g_out.equals(g_out[i][j])) {
                    changed = true;
                    g_out[i][j] = new_g_out;
                }
            }
        }
    } while (changed);


    Graph res;

    for (uint i = 0; i < n; ++i) {
        // building i's graph G without edges to i
        Graph g;
        g.n = clGraph.n;
        for (auto it = clGraph.edges.lower_bound(make_pair(i, 0));
             it != clGraph.edges.end() && it->first == i; ++it)
        {
            const uint j = it->second;

            g.merge( g_out[j][i] );
        }

        for (auto it = clGraph.edges.lower_bound(make_pair(i, 0));
             it != clGraph.edges.cend() && it->first == i; ++it)
        {
            const uint j = it->second;

            if (DiffColor(addrs[i], addrs[j])) {
                //Connecting nodes in the j's neighboorhood
                vector<uint> hood;
                hood.push_back(i);
                for (auto jt = g.edges.lower_bound(make_pair(j, 0));
                     jt != g.edges.cend() && jt->first == j; ++jt)
                {
                    const uint k = jt->second;

                    if (DiffColor(addrs[j], addrs[k])) {
                        hood.push_back(k);
                    }
                }

                const uint sz = hood.size();

                vector<Addr> hoodAddrs(sz);
                for (uint k = 0; k < sz; ++k) {
                    hoodAddrs[k] = addrs[hood[k]];
                }

                //sort hood by addr
                for (uint k = 0; k < sz; ++k) {
                    for (uint kk = k + 1; kk < sz; ++kk) {
                        if (hoodAddrs[k] > hoodAddrs[kk]) {
                            swap(hoodAddrs[k], hoodAddrs[kk]);
                            swap(hood[k], hood[kk]);
                        }
                    }
                }

                auto l = hood.cbegin();
                auto r = hood.cend();

                Addr bit = FirstBit;
                Addr mAddr = FirstBit;
                while (r - l > 1) {
                    auto m = lower_bound(l, r, mAddr);

                    if ((m - l > 0) && (r - m > 0)) {
                        auto best_l = l;
                        auto best_r = m;
                        Addr bestDist = *l ^ *m;

                        for (auto it_l = l; it_l < m; ++it_l) {
                            for (auto it_r = m; it_r < r; ++it_r) {
                                Addr dist = *it_l ^ *it_r;

                                if (dist < bestDist) {
                                    bestDist = dist;
                                    best_l = it_l;
                                    best_r = it_r;
                                }
                            }
                        }

                        if ((addrs[i] == *best_l) || (addrs[i] == *best_r)) {
                            res.addEdge( *(hood.cbegin() + (best_l - hoodAddrs.cbegin())),
                                         *(hood.cbegin() + (best_r - hoodAddrs.cbegin())) );
                        }
                    }

                    if (addrs[i] < *m) {
                        r = m;
                    } else {
                        l = m;
                    }

                    mAddr = mAddr ^ bit ^ addrs[i];
                    bit >>= 1;

                    assert(bit != 0);
                }   // while (l < r)

                //Enter Neighborhood stuff
            } else {    //if (DiffColor(addrs[i], addrs[j])) {
                res.addEdge(i, j);
            }
        }
    }

    return res;
}





