#ifndef SIM_H_
#define SIM_H_

#include <iostream>

#include "bmlrp.h"
#include "graph.h"

using std::cerr;
using std::endl;

struct Point {
  float x;
  float y;
};

class Network {
 public:
  Network() {}

  Network(const Graph& graph, const std::vector<Addr>& addrs,
          const std::vector<Point>& points) {
    Network::graph = graph;
    Network::addrs = addrs;
    Network::points = points;
  }

  Graph graph;
  std::vector<Addr> addrs;
  std::vector<Point> points;
};


Network GetNetworkLevel(const Network& net_level0, int level);

Network Random(int n, float r_coeff, float random_edges_ratio_nodes);
std::vector<float> GetAverageNodeDegrees(const Network& net_level0,
                                         int max_level);

Network Manual0();
Network Manual1();
Network Manual2();
Network Manual3();
Network Manual4();
Network Manual5();

#endif  // SIM_H_
