#ifndef GRAPH_H
#define GRAPH_H\

#include "stable.h"

class Graph {
public:
    Graph() {
        n = 0;
    }

    Graph(int n) {
        Graph::n = n;
    }

    void AddEdge(int a, int b) {
        edges.insert( std::make_pair(a, b) );
        edgesReverse.insert( std::make_pair(b, a) );
    }

    void AddEdgeBidirectional(int a, int b) {
        AddEdge(a, b);
        AddEdge(b, a);
    }

    void RemoveEdge(int a, int b) {
        edges.erase( std::make_pair(a, b) );
        edgesReverse.erase( std::make_pair(b, a) );
    }

    void RemoveEdgeBidirectional(int a, int b) {
        RemoveEdge(a, b);
        RemoveEdge(b, a);
    }

//    void RemoveVertex(int a) {
//        std::vector< std::pair<int, int> > toRemove;

//        for (auto it = edges.lower_bound( std::make_pair(a, 0) );
//             it != edges.cend() && it->first == a; ++it)
//        {
//            toRemove.push_back(it->first);
//        }

//        for (auto it = edgesReverse.lower_bound( std::make_pair(a, 0) );
//             it != edgesReverse.cend() && it->first == a; ++it)
//        {
//            toRemove.push_back(it->first);
//        }

//        for (int32_t i = 0; i < toRemove.size(); ++i) {
//            RemoveEdge(toRemove[i].first, toRemove[i].second);
//        }
//    }

    bool EdgeExists(int a, int b) const {
        return ( edges.find(std::make_pair(a, b)) != edges.cend() );
    }

    bool EdgeExistsBidirectional(int a, int b) const {
        return EdgeExists(a, b) && EdgeExists(b, a);
    }

    std::vector<int> GetDirectSuccessors(int node) const {
        std::vector<int> res;

        for (auto it = edges.lower_bound( std::make_pair(node, 0) );
             it != edges.cend() && it->first == node; ++it)
        {
            res.push_back(it->second);
        }

        return res;
    }

    std::vector<int> GetDirectPredecessors(int node) const {
        std::vector<int> res;

        for (auto it = edgesReverse.lower_bound( std::make_pair(node, 0) );
             it != edgesReverse.cend() && it->first == node; ++it)
        {
            res.push_back(it->second);
        }

        return res;
    }

    bool Symmetric() const {
        return (edges == edgesReverse);
    }

    int n;

    std::set< std::pair<int, int> > edges;
    std::set< std::pair<int, int> > edgesReverse;
};

#endif // GRAPH_H
