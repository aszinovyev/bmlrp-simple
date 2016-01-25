#include <Rcpp.h>
#include "stable.h"

#include "graph.h"
#include "bmlrp.h"
#include "misc.h"
#include "sim.h"
#include "export.h"


GraphInfo getLevel(GraphInfo graphInfo, int level) {
    Graph graph;
    vector<Addr> addrs;
    tie(graph, addrs, ignore) = graphInfo;

    while (level > 0) {
        graph = NextLevel(graph, addrs);

        for (uint i = 0; i < addrs.size(); ++i) {
            addrs[i] <<= 1;
        }

        --level;
    }

    return make_tuple(graph, get<1>(graphInfo), get<2>(graphInfo));
}

// [[Rcpp::export]]
GraphWrapper Random_R(int level, int format) {
    //return GraphWrapper( getLevel(Random(10, 10, 3.7), level), format );
    return GraphWrapper( getLevel(Random(500, 70, 7), level), format );
}

// [[Rcpp::export]]
GraphWrapper Manual0_R(int level, int format) {
    return GraphWrapper( getLevel(Manual0(), level), format );
}
