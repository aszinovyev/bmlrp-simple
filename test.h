#ifndef TEST_H_
#define TEST_H_

#include "bmlrp.h"
#include "graph.h"

void TestNextLevel(const Graph& graph, const std::vector<Addr>& addrs,
                   int nextLevel);
bool IsGraphConnected(const Graph& graph);

#endif  // TEST_H_
