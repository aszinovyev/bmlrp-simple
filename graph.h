#ifndef GRAPH_H
#define GRAPH_H

using namespace std;

//template<class uint = uint>
class Graph {
public:
    Graph() {
        n = 0;
    }

    Graph(uint n) {
        Graph::n = n;
    }

    void AddEdge(uint a, uint b) {
        edges.insert( make_pair(a, b) );
        edgesReverse.insert( make_pair(b, a) );
    }

    void AddEdgeBidirectional(uint a, uint b) {
        AddEdge(a, b);
        AddEdge(b, a);
    }

    void RemoveEdge(uint a, uint b) {
        edges.erase( make_pair(a, b) );
        edgesReverse.erase( make_pair(b, a) );
    }

    void RemoveEdgeBidirectional(uint a, uint b) {
        RemoveEdge(a, b);
        RemoveEdge(b, a);
    }

//    void RemoveVertex(uint a) {
//        vector< pair<uint, uint> > toRemove;

//        for (auto it = edges.lower_bound( make_pair(a, 0) );
//             it != edges.cend() && it->first == a; ++it)
//        {
//            toRemove.push_back(it->first);
//        }

//        for (auto it = edgesReverse.lower_bound( make_pair(a, 0) );
//             it != edgesReverse.cend() && it->first == a; ++it)
//        {
//            toRemove.push_back(it->first);
//        }

//        for (uint32_t i = 0; i < toRemove.size(); ++i) {
//            RemoveEdge(toRemove[i].first, toRemove[i].second);
//        }
//    }

    bool EdgeExists(uint a, uint b) const {
        return ( edges.find(make_pair(a, b)) != edges.cend() );
    }

    bool EdgeExistsBidirectional(uint a, uint b) const {
        return EdgeExists(a, b) && EdgeExists(b, a);
    }

    vector<uint> GetDirectSuccessors(uint node) const {
        vector<uint> res;

        for (auto it = edges.lower_bound( make_pair(node, 0) );
             it != edges.cend() && it->first == node; ++it)
        {
            res.push_back(it->second);
        }

        return res;
    }

    vector<uint> GetDirectPredecessors(uint node) const {
        vector<uint> res;

        for (auto it = edgesReverse.lower_bound( make_pair(node, 0) );
             it != edgesReverse.cend() && it->first == node; ++it)
        {
            res.push_back(it->second);
        }

        return res;
    }

    bool Symmetric() const {
        return (edges == edgesReverse);
    }

    uint n;

    set< pair<uint, uint> > edges;
    set< pair<uint, uint> > edgesReverse;
};

#endif // GRAPH_H
