#include "network_r.h"

#include <vector>
#include <string>

#include "bmlrp.h"
#include "debug.h"

using std::vector;
using std::string;

Network_R::Network_R(const Network& net, const string& filter, char label) {
  Graph graph = net.graph;
  vector<Addr> addrs = net.addrs;
  vector<Point> points = net.points;

  const int n = net.graph.n;

  myassert(addrs.size() == n);
  myassert(points.size() == n);

  vector<int> include(n);
  int j = 0;
  for (int i = 0; i < n; ++i) {
    if (IncludeAddr(addrs[i], filter)) {
      include[i] = j++;
    } else {
      include[i] = -1;
    }
  }

  edges = Edges_R(graph, include);

  for (int i = 0; i < n; ++i) {
    if (include[i] != -1) {
      if (label < 0) {
        labels.push_back(std::to_string(i));
      } else {
        labels.push_back(AddrToString(addrs[i], label, false));
      }

      colors.push_back(addrs[i] & (Msb >> filter.size()));

      coords.push_back(points[i].x);
      coords.push_back(points[i].y);
    }
  }
}

bool Network_R::IncludeAddr(Addr a, const string& filter) {
  for (uint i = 0; i < filter.size(); ++i) {
    char ch = filter[i] - '0';
    myassert(ch == 0 || ch == 1);

    if (static_cast<bool>(a & Msb) != ch) {
      return false;
    }

    a <<= 1;
  }

  return true;
}

vector<int> Network_R::Edges_R(Graph graph, const vector<int>& include) {
  vector<int> res;

  for (int i = 0; i < graph.n; ++i) {
    vector<int> succ = graph.GetDirectSuccessors(i);

    for (uint j = 0; j < succ.size(); ++j) {
      int to = succ[j];

      if ((to > i) && (include[i] != -1) && (include[to] != -1)) {
        res.push_back(include[i]);
        res.push_back(include[to]);
      }
    }
  }

  return res;
}
