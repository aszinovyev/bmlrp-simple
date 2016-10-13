#include "stable.h"
#include "graph.h"
#include "bmlrp.h"
#include "misc.h"
#include "debug.h"
#include "test.h"

using std::cerr;
using std::endl;

Addr Prefix(const Addr addr, const int len) {
    return (addr >> (sizeof(addr)*8 - len));
}

void DFS0(int node, const Graph& graph, const std::vector<Addr>& addrs,
         const int nextLevel, std::vector<bool>& used)
{
    used[node] = true;

    std::vector<int> succ = graph.GetDirectSuccessors(node);
    for (uint i = 0; i < succ.size(); ++i) {
        int to = succ[i];
        myassert(to != node);

        if (!used[to]) {
            myassert(Prefix(addrs[node], nextLevel) == Prefix(addrs[to], nextLevel));

            DFS0(to, graph, addrs, nextLevel, used);
        }
    }
}

void TestNextLevel(const Graph& graph, const std::vector<Addr>& addrs, const int nextLevel) {
    myassert(graph.Symmetric());

    std::set<Addr> usedPrefixes;
    std::vector<bool> usedNodes(graph.n, false);

    for (int i = 0; i < graph.n; ++i) {
        if (!usedNodes[i]) {
            Addr prefix = Prefix(addrs[i], nextLevel);

            myassert(usedPrefixes.find(prefix) == usedPrefixes.cend());
            usedPrefixes.insert(prefix);

            DFS0(i, graph, addrs, nextLevel, usedNodes);
        }
    }
}

int DFS1(int node, const Graph& graph, std::vector<bool>& used) {
    used[node] = true;

    int res = 1;

    std::vector<int> succ = graph.GetDirectSuccessors(node);
    for (uint i = 0; i < succ.size(); ++i) {
        int to = succ[i];

        if (!used[to]) {
            res += DFS1(to, graph, used);
        }
    }

    return res;
}

bool IsGraphConnected(const Graph& graph) {
    cerr << "Checking that graph is connected" << endl;

    set_stack_size((1<<20) + 200 * graph.n);  // 1MB + 200 bytes per node

    std::vector<bool> used(graph.n, false);
    return (DFS1(0, graph, used) == graph.n);
}
