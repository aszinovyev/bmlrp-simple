#ifndef GRAPH_H_
#define GRAPH_H_

#include <set>
#include <vector>

class Graph {
 public:
  Graph();
  explicit Graph(int n);

  void AddEdge(int a, int b);
  void AddEdgeBidirectional(int a, int b);

  void RemoveEdge(int a, int b);
  void RemoveEdgeBidirectional(int a, int b);

  bool EdgeExists(int a, int b) const;
  bool EdgeExistsBidirectional(int a, int b) const;

  std::vector<int> GetDirectSuccessors(int node) const;
  std::vector<int> GetDirectPredecessors(int node) const;

  bool Symmetric() const;

  int n;

  std::set< std::pair<int, int> > edges;
  std::set< std::pair<int, int> > edgesReverse;
};

#endif  // GRAPH_H_
