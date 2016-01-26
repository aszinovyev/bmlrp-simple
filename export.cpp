#include <Rcpp.h>
#include "stable.h"

#include "myassert.h"
#include "graph.h"
#include "bmlrp.h"
#include "misc.h"
#include "sim.h"
#include "export.h"


void Reset() {
    Gen.seed(0xFA2B5E01);
}

// [[Rcpp::export]]
Network_R Random_R(int n, float r_coeff, int level, string filter, int labelLen) {
    Reset();
    return Network_R( GetNetworkLevel(Random(n, r_coeff), level), filter, labelLen);
}

// [[Rcpp::export]]
Network_R Manual0_R(int level, string filter, int labelLen) {
    Reset();
    return Network_R( GetNetworkLevel(Manual0(), level), filter, labelLen );
}

// [[Rcpp::export]]
Network_R Manual1_R(int level, string filter, int labelLen) {
    Reset();
    return Network_R( GetNetworkLevel(Manual1(), level), filter, labelLen );
}

// [[Rcpp::export]]
Network_R Manual2_R(int level, string filter, int labelLen) {
    Reset();
    return Network_R( GetNetworkLevel(Manual2(), level), filter, labelLen );
}

// [[Rcpp::export]]
Network_R Manual3_R(int level, string filter, int labelLen) {
    Reset();
    return Network_R( GetNetworkLevel(Manual3(), level), filter, labelLen );
}

// [[Rcpp::export]]
Network_R Manual4_R(int level, string filter, int labelLen) {
    Reset();
    return Network_R( GetNetworkLevel(Manual4(), level), filter, labelLen );
}
