#include "bmlrp.h"

#include <algorithm>
#include <vector>
#include <queue>

#include "debug.h"
#include "graph.h"
#include "misc.h"
#include "sim.h"
#include "test.h"

using std::cerr;
using std::endl;
using std::vector;

const Addr Msb = ((Addr)-1 >> 1) + 1;

void connectInside(const vector<int>& circle, const vector<Addr>& addrs,
                   int l, int r, Addr bit, Graph* appendTo) {
  myassert(bit != 0);

  if (r - l < 2) {
    return;
  }

  int m = l;
  while ((m < r) && ((addrs[circle[m]] & bit) == 0)) {
    ++m;
  }

  if ((m - l > 0) && (r - m > 0)) {
    int best_i = l;
    int best_j = m;
    Addr best_dist = addrs[circle[l]] ^ addrs[circle[m]];

    for (int i = l; i < m; ++i) {
      for (int j = m; j < r; ++j) {
        Addr dist = addrs[circle[i]] ^ addrs[circle[j]];
        if (dist < best_dist) {
          best_dist = dist;
          best_i = i;
          best_j = j;
        }
      }
    }

    appendTo->AddEdgeBidirectional(circle[best_i], circle[best_j]);
  }

  bit >>= 1;
  connectInside(circle, addrs, l, m, bit, appendTo);
  connectInside(circle, addrs, m, r, bit, appendTo);
}

// Connect nodes inside circle. circle must be sorted.
void connectInside(const vector<int>& circle, const vector<Addr>& addrs,
                   Graph* appendTo) {
  connectInside(circle, addrs, 0, circle.size(), Msb, appendTo);
}

// Connect 2 circles together.
void connectCircles(const vector<int>& circle0, const vector<int>& circle1,
                    const vector<Addr>& addrs, Graph* appendTo) {
  if (circle0.empty()) {
    return;
  }
  myassert(!circle1.empty());

  Addr best_dist = addrs[circle0[0]] ^ addrs[circle1[0]];
  int best_i = 0;
  int best_j = 0;

  for (uint i = 0; i < circle0.size(); ++i) {
    for (uint j = 0; j < circle1.size(); ++j) {
      Addr dist = addrs[circle0[i]] ^ addrs[circle1[j]];
      if (dist < best_dist) {
        best_dist = dist;
        best_i = i;
        best_j = j;
      }
    }
  }

  if (circle0[best_i] != circle1[best_j]) {
    appendTo->AddEdgeBidirectional(circle0[best_i], circle1[best_j]);
  }
}

bool DiffColor(Addr a, Addr b) {
  return (a ^ b) & Msb;
}

bool SameColor(Addr a, Addr b) {
  return !DiffColor(a, b);
}

// Returns the next level graph.
// clGraph: current level graph
// addrs: vector of addresses shifted left by i, if clGraph is level i.
Graph NextLevel(const Graph& clGraph, const vector<Addr>& addrs) {
  const int n = clGraph.n;

  vector< vector<int> > circles(n);
  vector<int> radius(n, 0);

  struct BfsState {
    int node;  // the tracked node
    int location;  // the current location (vertex at which node is located)
  };

  std::queue<BfsState> q;
  for (int i = 0; i < n; ++i) {
    q.push({i, i});
  }

  // distance from the origin
  int dist = 0;

  while (!q.empty()) {
    std::queue<BfsState> qn;  // queue new

    while (!q.empty()) {
      int node = q.front().node;
      int loc = q.front().location;
      q.pop();

      vector<int> succ = clGraph.GetDirectSuccessors(loc);
      for (uint i = 0; i < succ.size(); ++i) {
        const int to = succ[i];
        if (DiffColor(addrs[node], addrs[to])) {
          if ((radius[to] == 0) || (radius[to] == dist + 1)) {
            radius[to] = dist + 1;
            circles[to].push_back(node);
            qn.push({node, to});
          }
        }
      }
    }

    q = qn;
    ++dist;
  }

  Graph res(n);

  // connect nodes in each circle
  for (int i = 0; i < n; ++i) {
    auto& circle = circles[i];

    // sort nodes by address
    sort(circle.begin(), circle.end(), [&addrs](int node1, int node2) {
      return addrs[node1] < addrs[node2];
    });

    // make each element unique
    auto it = std::unique(circle.begin(), circle.end());
    circle.resize(std::distance(circle.begin(), it));

    connectInside(circle, addrs, &res);
  }

  // connect same color neighbors and connect nodes in neighboring circles
  for (int i = 0; i < n; ++i) {
    vector<int> succ = clGraph.GetDirectSuccessors(i);
    for (uint j = 0; j < succ.size(); ++j) {
      const int to = succ[j];
      if (SameColor(addrs[i], addrs[to])) {
        // connect same color neighbors
        res.AddEdge(i, to);
        // connect nodes in neighboring circles
        connectCircles(circles[i], circles[to], addrs, &res);
      }
    }
  }

  return res;
}

Graph GetLevel(const Graph& level0, const vector<Addr>& addrs, int level) {
  myassert(level <= static_cast<int>(sizeof(Addr) * 8));
  myassert(IsGraphConnected(level0));

  Graph res = level0;

  vector<Addr> addrs_copy = addrs;

  for (int level_i = 1; level_i <= level; ++level_i) {
    res = NextLevel(res, addrs_copy);
    TestNextLevel(res, addrs, level_i);

    for (uint i = 0; i < addrs_copy.size(); ++i) {
      addrs_copy[i] <<= 1;
    }
  }

  return res;
}
