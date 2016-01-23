#include <Rcpp.h>
#include <vector>
#include <set>
#include <tuple>
#include "misc.h"
#include "bmlrp.h"
#include "sim.h"
#include "export.h"

vector<int> EdgesForR(Graph graph) {
    vector<int> res;
    for (int i = 0; i < graph.n; ++i) {
        for (auto it = graph.edges.lower_bound(make_pair(i, i));
             it != graph.edges.end() && it->first == i; ++it)
        {
            res.push_back(i);
            res.push_back(it->second);
        }
    }

    return res;
}


// [[Rcpp::export]]
GraphR RandomForR() {
    Graph graph;
    vector<Addr> addrs;
    vector<Point> points;
    tie(graph, addrs, points) = Random(10, 10, 3.7);

    GraphR res;
    res.edges = EdgesForR(graph);
    res.labels.resize(graph.n);
    res.colors.resize(graph.n);
    res.coords.resize(graph.n * 2);

    for (int i = 0; i < graph.n; ++i) {
        res.labels[i] = Binary(addrs[i], 4, false);
        res.colors[i] = res.labels[i][0] - '0';
        res.coords[i*2] = points[i].x;
        res.coords[i*2+1] = points[i].y;
    }

    return res;
}
