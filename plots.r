require(Rcpp)
require(igraph)

sourceCpp("export.cpp")

FromCpp <- function(v) {
    edges <- matrix( RandomForR() + 1, ncol=2, byrow=T)
    graph_from_edgelist(edges, F)
}

Random <- function() {
    plot( FromCpp(RandomForR()) )
}
