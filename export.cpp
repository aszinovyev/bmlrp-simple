#include "export.h"

#include "bmlrp.h"
#include "debug.h"
#include "graph.h"
#include "misc.h"
#include "sim.h"

using std::string;
using std::vector;

// [[Rcpp::export]]
void SetSeed_R(uint seed) {
  Gen.seed(seed);
}

// [[Rcpp::export]]
Network_R Random_R(int n, float r_coeff, float random_edges_ratio_nodes,
                   int level, string filter, int label) {
  return Network_R(
      GetNetworkLevel(Random(n, r_coeff, random_edges_ratio_nodes), level),
      filter, label);
}

// [[Rcpp::export]]
vector<float> RandomNodeDegrees_R(int n, float r_coeff,
                                  float random_edges_ratio_nodes,
                                  int max_level) {
  return GetAverageNodeDegrees(Random(n, r_coeff, random_edges_ratio_nodes),
                               max_level);
}

// [[Rcpp::export]]
Network_R Manual0_R(int level, string filter) {
  return Network_R(GetNetworkLevel(Manual0(), level), filter, 5);
}

// [[Rcpp::export]]
Network_R Manual1_R(int level, string filter) {
  return Network_R(GetNetworkLevel(Manual1(), level), filter, 5);
}

// [[Rcpp::export]]
Network_R Manual2_R(int level, string filter) {
  return Network_R(GetNetworkLevel(Manual2(), level), filter, 5);
}

// [[Rcpp::export]]
Network_R Manual3_R(int level, string filter) {
  return Network_R(GetNetworkLevel(Manual3(), level), filter, 5);
}

// [[Rcpp::export]]
Network_R Manual4_R(int level, string filter) {
  return Network_R(GetNetworkLevel(Manual4(), level), filter, 5);
}

// [[Rcpp::export]]
Network_R Manual5_R(int level, string filter) {
  return Network_R(GetNetworkLevel(Manual5(), level), filter, 5);
}
