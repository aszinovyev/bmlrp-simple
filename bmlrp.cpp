#include "stable.h"
#include "myassert.h"
#include "graph.h"
#include "bmlrp.h"
#include "misc.h"
#include "sim.h"


class State1 {
public:
    uint node;  //current position
    vector<uint> chain;
    uint ttl;

    State1() {
        node = 0;
        ttl = 0;
    }

    State1(uint node, uint ttl) {
        State1::node = node;
        State1::ttl = ttl;
    }

    State1(uint node, vector<uint> chain, uint ttl) {
        State1::node = node;
        State1::chain = chain;
        State1::ttl = ttl;
    }
};

class State2 {
public:
    uint node;
    uint ttl;
    uint dist;

    State2() {
        node = 0;
        ttl = 0;
        dist = 0;
    }

    State2(uint node, uint ttl, uint dist) {
        State2::node = node;
        State2::ttl = ttl;
        State2::dist = dist;
    }

    bool operator<(const State2& other) const {
        if (ttl > other.ttl) {
            return true;
        }
        if (ttl < other.ttl) {
            return false;
        }
        if (dist < other.dist) {
            return true;
        }
        if (dist > other.dist) {
            return false;
        }
        return (node < other.node);
    }
};

bool SameColor(Addr a, Addr b);

class Neighborhood {
public:
    uint node;
    vector< pair<Addr, uint> > neighborhood;

    Neighborhood() {}

    Neighborhood(const Graph& graph, uint node, const vector<Addr>& addrs) {
        Neighborhood::node = node;

        for (uint i = 0; i < graph.edges[node].size(); ++i) {
            const uint to = graph.edges[node][i];

            if (!SameColor(addrs[node], addrs[to])) {
                neighborhood.push_back( make_pair(addrs[to], to) );
            }
        }

        sort(neighborhood.begin(), neighborhood.end());
    }

    bool empty() const {
        return neighborhood.empty();
    }

    void connectInside(uint myNode, Addr myAddr, Graph& appendTo) {
        uint l = 0;
        uint r = neighborhood.size();

        Addr bit = FirstBit;
        Addr mAddr = FirstBit;

        while (r - l > 1) {
            myassert(bit != 0);

            uint m = l;
            while ((m < r) && (neighborhood[m].first < mAddr)) {
                ++m;
            }

            if ((m - l > 0) && (r - m > 0)) {
                uint best_l = l;
                uint best_r = m;
                Addr bestDist = neighborhood[l].first ^ neighborhood[m].first;

                for (uint il = l; il < m; ++il) {
                    for (uint ir = m; ir < r; ++ir) {
                        Addr dist = neighborhood[il].first ^ neighborhood[ir].first;

                        if (dist < bestDist) {
                            bestDist = dist;
                            best_l = il;
                            best_r = ir;
                        }
                    }
                }

                uint a = neighborhood[best_l].second;
                uint b = neighborhood[best_r].second;
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

    void connectTo(const Neighborhood& to, Addr myNode, Graph& appendTo) const {
        myassert(!empty());
        myassert(!to.empty());

        Addr bestDist = neighborhood[0].first ^ to.neighborhood[0].first;
        uint best0 = neighborhood[0].second;
        uint best1 = to.neighborhood[0].second;

        for (uint i = 0; i < neighborhood.size(); ++i) {
            for (uint j = 0; j < to.neighborhood.size(); ++j) {
                Addr dist = neighborhood[i].first ^ to.neighborhood[j].first;

                if (dist < bestDist) {
                    bestDist = dist;
                    best0 = neighborhood[i].second;
                    best1 = to.neighborhood[j].second;
                }
            }
        }

        if ((best0 == myNode) && (best1 != myNode)) {
            appendTo.AddDirEdge(best0, best1);
        }
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

    queue<State1> q;
    for (uint i = 0; i < n; ++i) {
        q.push(State1(i, inf));
    }

    //bool used[n][n] = {false};

    uint iter = 0;

    while (!q.empty()) {
        queue<State1> qn;    //queue new

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

                                g[to].AddEdge(a, b);
                            }
                        } else {
                            qn.push(State1(to, chain, ttl - 1));
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
//        g[i].Print();
//    }
//    cout << endl;


    Graph res(n);

    for (uint i = 0; i < n; ++i) {
        for (uint j = 0; j < g[i].edges[i].size(); ++j) {
            const uint jto = g[i].edges[i][j];

            if (SameColor(addrs[i], addrs[jto])) {
                res.AddDirEdge(i, jto);
            } else {
                Neighborhood neighborhood(g[i], jto, addrs);
                neighborhood.connectInside(i, addrs[i], res);
            }
        }

        for (uint j = 0; j < g[i].edges[i].size(); ++j) {
            const uint jto = g[i].edges[i][j];

            if (!SameColor(addrs[i], addrs[jto])) {
                Neighborhood myNeighborhood(g[i], jto, addrs);

                bool used[n] = {false};

                set<State2> q;
                q.insert(State2(jto, inf, 1));

                while (!q.empty()) {
                    State2 s = *q.begin();
                    uint node = s.node;
                    uint ttl = s.ttl;
                    uint d = s.dist;
                    q.erase(q.begin());

                    if (!used[node]) {
                        used[node] = true;

                        Neighborhood neighborhood(g[i], node, addrs);
                        if ((d > 1) && !neighborhood.empty()) {
                            myNeighborhood.connectTo(neighborhood, i, res);
                        } else {
                            if (d > dist[node]) {
                                ttl = min(ttl, dist[node]);
                            }

                            if (ttl > 1) {
                                for (uint k = 0; k < g[i].edges[node].size(); ++k) {
                                    const uint kto = g[i].edges[node][k];

                                    if (!used[kto] && SameColor(addrs[jto], addrs[kto])) {
                                        q.insert(State2(kto, ttl - 1, d + 1));
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    res.Simplify();

    myassert(res.Symmetric());
    return res;
}

Graph GetLevel(const Graph& level0, const vector<Addr>& addrs, int level) {
    Graph res = level0;
    myassert(res.Symmetric());

    vector<Addr> addrs_copy = addrs;

    while (level > 0) {
        res = NextLevel(res, addrs_copy);

        for (uint i = 0; i < addrs_copy.size(); ++i) {
            addrs_copy[i] <<= 1;
        }

        --level;
    }

    return res;
}
