#include "graph.h"

#include <vector>

using std::vector;

Graph::Graph() {
  n = 0;
}

Graph::Graph(int n) {
  Graph::n = n;
}

void Graph::AddEdge(int a, int b) {
  edges.insert(std::make_pair(a, b));
  edgesReverse.insert(std::make_pair(b, a));
}

void Graph::AddEdgeBidirectional(int a, int b) {
  AddEdge(a, b);
  AddEdge(b, a);
}

void Graph::RemoveEdge(int a, int b) {
  edges.erase(std::make_pair(a, b));
  edgesReverse.erase(std::make_pair(b, a));
}

void Graph::RemoveEdgeBidirectional(int a, int b) {
  RemoveEdge(a, b);
  RemoveEdge(b, a);
}

//    void RemoveVertex(int a) {
//        vector< std::pair<int, int> > toRemove;

//        for (auto it = edges.lower_bound(std::make_pair(a, 0));
//             it != edges.cend() && it->first == a; ++it)
//        {
//            toRemove.push_back(it->first);
//        }

//        for (auto it = edgesReverse.lower_bound(std::make_pair(a, 0));
//             it != edgesReverse.cend() && it->first == a; ++it)
//        {
//            toRemove.push_back(it->first);
//        }

//        for (int32_t i = 0; i < toRemove.size(); ++i) {
//            RemoveEdge(toRemove[i].first, toRemove[i].second);
//        }
//    }

bool Graph::EdgeExists(int a, int b) const {
  return (edges.find(std::make_pair(a, b)) != edges.cend());
}

bool Graph::EdgeExistsBidirectional(int a, int b) const {
  return EdgeExists(a, b) && EdgeExists(b, a);
}

vector<int> Graph::GetDirectSuccessors(int node) const {
  vector<int> res;

  for (auto it = edges.lower_bound(std::make_pair(node, 0));
       it != edges.cend() && it->first == node; ++it) {
    res.push_back(it->second);
  }

  return res;
}

vector<int> Graph::GetDirectPredecessors(int node) const {
  vector<int> res;

  for (auto it = edgesReverse.lower_bound(std::make_pair(node, 0));
       it != edgesReverse.cend() && it->first == node; ++it) {
    res.push_back(it->second);
  }

  return res;
}

bool Graph::Symmetric() const {
  return (edges == edgesReverse);
}
