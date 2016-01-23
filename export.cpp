#include <vector>
#include <tuple>
#include "misc.h"
#include "graph.h"
#include "sim.h"

vector<int> ForR(Graph graph) {
    vector<int> res;
    for (int i = 0; i < graph.n; ++i) {
        for (uint j = 0; j < graph.edges[i].size(); ++j) {
            int to = graph.edges[i][j];

            if (to > i) {
                res.push_back(i);
                res.push_back(to);
            }
        }
    }

    return res;
}


// [[Rcpp::export]]
vector<int> RandomForR() {
    return ForR( get<0>( Random(10, 10, 3.7) ) );
}
