#include <Rcpp.h>
#include "stable.h"

#include "misc.h"
#include "graph.h"
#include "bmlrp.h"
#include "debug.h"
#include "sim.h"
#include "export.h"


// [[Rcpp::export]]
void SetSeed_R(uint seed) {
    Gen.seed(seed);
}

// [[Rcpp::export]]
Network_R Random_R(int n, float r_coeff, float random_edges_ratio_nodes,
                                         int level, string filter, int label)
{
    return Network_R( GetNetworkLevel(Random(n, r_coeff, random_edges_ratio_nodes), level), filter, label);
}

// [[Rcpp::export]]
Network_R Overlay_R(int n, float m, int level, string filter, int label) {
    return Network_R( GetNetworkLevel(Overlay(n, m), level), filter, label);
}

// [[Rcpp::export]]
Network_R Manual0_R(int level, string filter) {
    return Network_R( GetNetworkLevel(Manual0(), level), filter, 5 );
}

// [[Rcpp::export]]
Network_R Manual1_R(int level, string filter) {
    return Network_R( GetNetworkLevel(Manual1(), level), filter, 5 );
}

// [[Rcpp::export]]
Network_R Manual2_R(int level, string filter) {
    return Network_R( GetNetworkLevel(Manual2(), level), filter, 5 );
}

// [[Rcpp::export]]
Network_R Manual3_R(int level, string filter) {
    return Network_R( GetNetworkLevel(Manual3(), level), filter, 5 );
}

// [[Rcpp::export]]
Network_R Manual4_R(int level, string filter) {
    return Network_R( GetNetworkLevel(Manual4(), level), filter, 5 );
}
