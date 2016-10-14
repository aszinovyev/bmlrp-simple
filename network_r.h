#ifndef NETWORK_R_H_
#define NETWORK_R_H_

#include <vector>
#include <string>

#include "graph.h"
#include "sim.h"

class Network_R {
 public:
  Network_R() {}
  Network_R(const Network& net, const std::string& filter, char label);

  std::vector<int> edges;
  std::vector<std::string> labels;
  std::vector<bool> colors;
  std::vector<float> coords;  // x1, y1, x2, y2, ...

 private:
  bool IncludeAddr(Addr a, const std::string& filter);
  std::vector<int> Edges_R(Graph graph, const std::vector<int>& include);
};

#endif  // NETWORK_R_H_
