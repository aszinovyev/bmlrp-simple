#include "stable.h"
#include "graph.h"
#include "bmlrp.h"
#include "misc.h"

class State {
public:
    uint node;  //current position
    vector<uint> chain;
    uint ttl;

    State() {
        node = 0;
        ttl = 0;
    }

    State(uint node, uint ttl) {
        State::node = node;
        State::ttl = ttl;
    }

    State(uint node, vector<uint> chain, uint ttl) {
        State::node = node;
        State::chain = chain;
        State::ttl = ttl;
    }
};


bool SameColor(Addr a, Addr b) {
    return ~(a ^ b) & FirstBit;
}

// cl == current level
Graph NextLevel(const Graph& clGraph, const vector<Addr>& addrs) {
    const uint n = clGraph.n;
    const uint inf = (uint)-1;

    Graph g[n](n);

    // min dist to opposite color
    uint dist[n];
    memset(dist, -1, sizeof(dist));     //filling dist[n] with inf

    queue<State> q;
    for (uint i = 0; i < n; ++i) {
        q.push(State(i, inf));
    }

    //bool used[n][n] = {false};

    uint iter = 0;

    while (!q.empty()) {
        queue<State> qn;    //queue new

        while (!q.empty()) {
            uint node = q.front().node;

            vector<uint> chain = q.front().chain;
            chain.push_back(node);

            uint ttl = q.front().ttl;
            if (iter > dist[node]) {
                ttl = min(ttl, dist[node]);
            }

            q.pop();

            if (iter > 0) {
                dist[node] = min(dist[node], iter);
            }

            if (ttl > 0) {
                for (uint i = 0; i < clGraph.edges[node].size(); ++i) {
                    const uint to = clGraph.edges[node][i];

                    // check that neighbor to is not in the chain
                    if (find(chain.cbegin(), chain.cend(), to) == chain.cend()) {
                        if (SameColor(addrs[chain[0]], addrs[to])) {
                            for (uint j = 0; j < chain.size() - 1; ++j) {
                                uint a = chain[j];
                                uint b = chain[j + 1];

                                g[to].edges[a].push_back(b);
                                g[to].edges[b].push_back(a);
                            }
                        } else {
                            qn.push(State(to, chain, ttl));
                        }
                    }
                }
            }
        }

        q = qn;
        ++iter;
    }

    // removing duplicates in graphs g[i]
    for (uint i = 0; i < n; ++i) {
        for (uint j = 0; j < n; ++j) {
            sort(g[i].edges[j].begin(), g[i].edges[j].end());

            auto tail = unique(g[i].edges[j].begin(), g[i].edges[j].end());
            g[i].edges[j].resize( distance(g[i].edges[j].begin(), tail) );
        }
    }

    // print g
    for (uint i = 0; i < n; ++i) {
        cout << "g of " << i << " :  ";

        for (uint j = 0; j < n; ++j) {
            for (uint k = 0; k < g[i].edges[j].size(); ++k) {
                const uint to = g[i].edges[j][k];
                if (to >= j) {
                    cout << j << "-" << to << " ";
                }
            }
        }

        cout << endl;
    }
    cout << endl;


    Graph res(n);

    for (uint i = 0; i < n; ++i) {

        for (uint j = 0; j < clGraph.edges[i].size(); ++j) {
            const uint jto = clGraph.edges[i][j];

            if (SameColor(addrs[i], addrs[jto])) {
                res.edges[i].push_back(jto);
            } else {
                vector< pair<Addr, uint> > hood;

                for (uint k = 0; k < clGraph.edges[jto].size(); ++k) {
                    const uint kto = clGraph.edges[jto][k];

                    if (SameColor(addrs[i], addrs[kto])) {
                        hood.push_back( make_pair(addrs[kto], kto) );
                    }
                }

                sort(hood.begin(), hood.end());


            }
        }

    }

    return res;
}





