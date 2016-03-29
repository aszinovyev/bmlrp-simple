#include "stable.h"
#include "graph.h"
#include "bmlrp.h"
#include "misc.h"
#include "debug.h"
#include "test.h"

Addr Prefix(const Addr addr, const int len) {
    return (addr >> (sizeof(addr)*8 - len));
}

void DFS0(uint node, const Graph& graph, const vector<Addr>& addrs,
         const int nextLevel, vector<bool>& used)
{
    used[node] = true;

    vector<uint> succ = graph.GetDirectSuccessors(node);
    for (uint i = 0; i < succ.size(); ++i) {
        uint to = succ[i];

        if (!used[to]) {
            myassert(Prefix(addrs[node], nextLevel) == Prefix(addrs[to], nextLevel));

            DFS0(to, graph, addrs, nextLevel, used);
        }
    }
}

void TestNextLevel(const Graph& graph, const vector<Addr>& addrs, const int nextLevel) {
    if (!graph.Symmetric()) {
        PrintGraph(graph);
        myassert(0);
    }

    set<Addr> usedPrefixes;
    vector<bool> usedNodes(graph.n, false);

    for (uint i = 0; i < graph.n; ++i) {
        if (!usedNodes[i]) {
            Addr prefix = Prefix(addrs[i], nextLevel);

            myassert(usedPrefixes.find(prefix) == usedPrefixes.cend());
            usedPrefixes.insert(prefix);

            DFS0(i, graph, addrs, nextLevel, usedNodes);
        }
    }
}

uint DFS1(uint node, const Graph& graph, vector<bool>& used) {
    used[node] = true;

    uint res = 1;

    vector<uint> succ = graph.GetDirectSuccessors(node);
    for (uint i = 0; i < succ.size(); ++i) {
        uint to = succ[i];

        if (!used[to]) {
            res += DFS1(to, graph, used);
        }
    }

    return res;
}

bool IsGraphConnected(const Graph& graph) {
    vector<bool> used(graph.n, false);

    return (DFS1(0, graph, used) == graph.n);
}
