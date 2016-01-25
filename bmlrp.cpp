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

bool SameColor(Addr a, Addr b);

class Hood {
public:
    uint node;
    vector< pair<Addr, uint> > hood;

    Hood() {}

    Hood(const Graph& graph, uint node, const vector<Addr>& addrs) {
        Hood::node = node;

        for (uint i = 0; i < graph.edges[node].size(); ++i) {
            const uint to = graph.edges[node][i];

            if (!SameColor(addrs[node], addrs[to])) {
                hood.push_back( make_pair(addrs[to], to) );
            }
        }

        sort(hood.begin(), hood.end());
    }

    bool empty() const {
        return hood.empty();
    }

    void connectInside(uint myNode, Addr myAddr, Graph& appendTo) {
        uint l = 0;
        uint r = hood.size();

        Addr bit = FirstBit;
        Addr mAddr = FirstBit;

        while (r - l > 1) {
            assert(bit != 0);

            uint m = l;
            while ((m < r) && (hood[m].first < mAddr)) {
                ++m;
            }

            if ((m - l > 0) && (r - m > 0)) {
                uint best_l = l;
                uint best_r = m;
                Addr bestDist = hood[l].first ^ hood[m].first;

                for (uint il = l; il < m; ++il) {
                    for (uint ir = m; ir < r; ++ir) {
                        Addr dist = hood[il].first ^ hood[ir].first;

                        if (dist < bestDist) {
                            bestDist = dist;
                            best_l = il;
                            best_r = ir;
                        }
                    }
                }

                uint a = hood[best_l].second;
                uint b = hood[best_r].second;
                if (myNode == a) {
                    appendTo.AddDirEdge(a, b);
                } else if (myNode == b) {
                    appendTo.AddDirEdge(b, a);
                }
            }

            if (myAddr < mAddr) {
                r = m;
            } else {
                l = m;
            }

            mAddr = mAddr ^ bit ^ (myAddr & bit);
            bit >>= 1;
            mAddr = mAddr | bit;
        }   // while (r - l > 1)
    }

    void connectTo(const Hood& to, Addr myNode, Graph& appendTo) const {
        assert(!empty());
        assert(!to.empty());

        Addr bestDist = hood[0].first ^ to.hood[0].first;
        uint best0 = hood[0].second;
        uint best1 = to.hood[0].second;

        for (uint i = 0; i < hood.size(); ++i) {
            for (uint j = 0; j < to.hood.size(); ++j) {
                Addr dist = hood[i].first ^ to.hood[j].first;

                if (dist < bestDist) {
                    bestDist = dist;
                    best0 = hood[i].second;
                    best1 = to.hood[j].second;
                }
            }
        }

        if (myNode == best0) {
            appendTo.AddDirEdge(best0, best1);
        }
    }
};


bool SameColor(Addr a, Addr b) {
    return ~(a ^ b) & FirstBit;
}

void EnterHood(uint node, uint myNode, const Graph& g, const Hood& myHood,
               bool* used, const vector<Addr>& addrs, Graph& appendTo) {
    if (used[node]) {
        return;
    }
    used[node] = true;

    Hood hood(g, node, addrs);
    if (!hood.empty()) {
        myHood.connectTo(hood, myNode, appendTo);
    } else {
        for (uint i = 0; i < g.edges[node].size(); ++i) {
            const uint to = g.edges[node][i];
            EnterHood(to, myNode, g, myHood, used, addrs, appendTo);
        }
    }
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
                            qn.push(State(to, chain, ttl - 1));
                        }
                    }
                }
            }
        }

        q = qn;
        ++iter;
    }

    // adding direct connections in g
    for (uint i = 0; i < n; ++i) {
        for (uint j = 0; j < clGraph.edges[i].size(); ++j) {
            const uint to = clGraph.edges[i][j];

            g[i].AddEdge(i, to);
        }
    }

    // removing duplicates in graphs g[i]
    for (uint i = 0; i < n; ++i) {
        g[i].Simplify();
    }

    // print g
//    for (uint i = 0; i < n; ++i) {
//        cout << "g of " << i << " :  ";

//        for (uint j = 0; j < n; ++j) {
//            for (uint k = 0; k < g[i].edges[j].size(); ++k) {
//                const uint to = g[i].edges[j][k];
//                if (to >= j) {
//                    cout << j << "-" << to << " ";
//                }
//            }
//        }

//        cout << endl;
//    }
//    cout << endl;


    Graph res(n);

    for (uint i = 0; i < n; ++i) {
        bool used[n] = {false};

        for (uint j = 0; j < g[i].edges[i].size(); ++j) {
            const uint jto = g[i].edges[i][j];

            if (SameColor(addrs[i], addrs[jto])) {
                res.AddDirEdge(i, jto);
            } else {
                used[jto] = true;

                Hood hood(g[i], jto, addrs);
                hood.connectInside(i, addrs[i], res);
            }
        }

        for (uint j = 0; j < g[i].edges[i].size(); ++j) {
            const uint jto = g[i].edges[i][j];

            if (!SameColor(addrs[i], addrs[jto])) {
                for (uint k = 0; k < g[i].edges[jto].size(); ++k) {
                    const uint kto = g[i].edges[jto][k];

                    if (SameColor(addrs[jto], addrs[kto])) {
                        EnterHood(kto, i, g[i], Hood(g[i], jto, addrs), used, addrs, res);
                    }
                }
            }
        }

    }

    res.Simplify();

    return res;
}





