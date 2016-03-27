#include "stable.h"
#include "misc.h"
#include "graph.h"
#include "bmlrp.h"
#include "sim.h"
#include "test.h"
#include "debug.h"

// node in directed acyclic graph
class DAG_Node {
public:
    uint node;
    shared_ptr<DAG_Node> parent;

    uint Head() {
        if (!parent) {
            return node;
        }
        return parent->Head();
    }

    bool Find(uint node) {
        return ( (DAG_Node::node == node) || (parent && parent->Find(node)) );
    }
};

class State1 {
public:
    uint node;  //current position
    shared_ptr<DAG_Node> chain;
    uint ttl;

    State1() {
        node = 0;
        ttl = 0;
    }

    State1(uint node, uint ttl) {
        State1::node = node;
        State1::ttl = ttl;
    }

    State1(uint node, shared_ptr<DAG_Node> chain, uint ttl) {
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

        vector<uint> succ = graph.GetDirectSuccessors(node);
        for (uint i = 0; i < succ.size(); ++i) {
            const uint to = succ[i];

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
                    appendTo.AddEdge(a, b);
                } else if (myNode == b) {
                    appendTo.AddEdge(b, a);
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
            appendTo.AddEdge(best0, best1);
        }
    }
};


shared_ptr<DAG_Node> DAG_Append(shared_ptr<DAG_Node> dagnode, uint node) {
    shared_ptr<DAG_Node> res(new DAG_Node);
    res->node = node;
    res->parent = dagnode;
    return res;
}

bool SameColor(Addr a, Addr b) {
    return ~(a ^ b) & FirstBit;
}

// cl == current level
Graph NextLevel(const Graph& clGraph, const vector<Addr>& addrs) {
    const uint n = clGraph.n;
    const uint inf = (uint)-1;

    Graph g[n];
    for (uint i = 0; i < n; ++i) {
        g[i] = Graph(n);
    }

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

            shared_ptr<DAG_Node> chain = DAG_Append(q.front().chain, node);

            uint ttl = q.front().ttl;
            if (iter > dist[node]) {
                ttl = min(ttl, dist[node]);
            }

            q.pop();

            if (iter > 0) {
                dist[node] = min(dist[node], iter);
            }

            if (ttl > 0) {
                vector<uint> succ = clGraph.GetDirectSuccessors(node);
                for (uint i = 0; i < succ.size(); ++i) {
                    const uint to = succ[i];

                    // check that neighbor `to` is not in the `chain`
                    if (!chain->Find(to)) {
                        if (SameColor(addrs[chain->Head()], addrs[to])) {
                            shared_ptr<DAG_Node> current = chain;

                            while(current->parent) {
                                g[to].AddEdgeBidirectional(current->parent->node, current->node);
                                current = current->parent;
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
        vector<uint> succ = clGraph.GetDirectSuccessors(i);
        for (uint j = 0; j < succ.size(); ++j) {
            const uint to = succ[j];

            g[i].AddEdgeBidirectional(i, to);
        }
    }

    // print g
//    for (uint i = 0; i < n; ++i) {
//        cout << "g of " << i << " :  ";
//        g[i].Print();
//    }
//    cout << endl;


    Graph res(n);

    for (uint i = 0; i < n; ++i) {
        vector<uint> succ = g[i].GetDirectSuccessors(i);

        for (uint j = 0; j < succ.size(); ++j) {
            const uint jto = succ[j];

            if (SameColor(addrs[i], addrs[jto])) {
                res.AddEdge(i, jto);
            } else {
                Neighborhood neighborhood(g[i], jto, addrs);
                neighborhood.connectInside(i, addrs[i], res);
            }
        }

        for (uint j = 0; j < succ.size(); ++j) {
            const uint jto = succ[j];

            if (!SameColor(addrs[i], addrs[jto])) {
                Neighborhood myNeighborhood(g[i], jto, addrs);

                vector<bool> used(n, false);

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
                                vector<uint> succk = g[i].GetDirectSuccessors(node);
                                for (uint k = 0; k < succk.size(); ++k) {
                                    const uint kto = succk[k];

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

    return res;
}

Graph GetLevel(const Graph& level0, const vector<Addr>& addrs, uint level) {
    myassert(level <= sizeof(Addr)*8);
    if (!IsGraphConnected(level0)) {
        cerr << "input graph is not connected" << endl;
        myassert(0);
    }

    Graph res = level0;

    vector<Addr> addrs_copy = addrs;

    for (uint leveli = 1; leveli <= level; ++leveli) {
        res = NextLevel(res, addrs_copy);
        TestNextLevel(res, addrs, leveli);

        for (uint i = 0; i < addrs_copy.size(); ++i) {
            addrs_copy[i] <<= 1;
        }
    }

    return res;
}
