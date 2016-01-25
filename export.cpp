#include <Rcpp.h>
#include "stable.h"

#include "graph.h"
#include "bmlrp.h"
#include "misc.h"
#include "sim.h"
#include "export.h"


// [[Rcpp::export]]
Network_R Random_R(int n, float r_coeff, int level, string filter, int labelLen) {
    return Network_R( GetNetworkLevel(Random(n, r_coeff), level), filter, labelLen);
}

// [[Rcpp::export]]
Network_R Manual0_R(int level, string filter, int labelLen) {
    return Network_R( GetNetworkLevel(Manual0(), level), filter, labelLen );
}

// [[Rcpp::export]]
Network_R Manual1_R(int level, string filter, int labelLen) {
    return Network_R( GetNetworkLevel(Manual1(), level), filter, labelLen );
}
