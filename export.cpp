#include <Rcpp.h>
#include <vector>
#include <set>
#include <tuple>
#include "misc.h"
#include "bmlrp.h"
#include "sim.h"
#include "export.h"

vector<uint> EdgesForR(Graph graph) {
    vector<uint> res;
    for (uint i = 0; i < graph.n; ++i) {
        for (uint j = 0; j < graph.edges[i].size(); ++j) {
            uint to = graph.edges[i][j];

            if (to > i) {
                res.push_back(i);
                res.push_back(to);
            }
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
