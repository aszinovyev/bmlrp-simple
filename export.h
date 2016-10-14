#ifndef EXPORT_H_
#define EXPORT_H_

#include <vector>
#include <Rcpp.h>
#include <string>

#include "debug.h"
#include "network_r.h"
#include "sim.h"

RCPP_EXPOSED_CLASS(Network_R)

RCPP_MODULE(md) {
  using namespace Rcpp;

  class_<Network_R>("Graph")
    .constructor()

    .field("edges", &Network_R::edges)
    .field("labels", &Network_R::labels)
    .field("colors", &Network_R::colors)
    .field("coords", &Network_R::coords)

    ;
}

#endif  // EXPORT_H_
