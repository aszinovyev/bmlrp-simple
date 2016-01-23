require(Rcpp)
require(igraph)

Sys.setenv("PKG_CXXFLAGS"="-std=c++11")

sourceCpp("export.cpp")

GraphFromCpp <- function(graph) {
    edges <- matrix( graph$edges + 1, ncol=2, byrow=T)

    res <- graph_from_edgelist(edges, F)
    V(res)$names <- graph$labels
    V(res)$colors <- ifelse(graph$colors, "gray75", "white")

    res
}

Plot <- function(graph, layout) {
    plot(graph, vertex.label = V(graph)$names, vertex.label.color = "black", vertex.color = V(graph)$colors, layout = layout)
}

Process <- function(data, plot = T) {
    graph <- GraphFromCpp(data)
    layout <- matrix(data$coords, ncol=2, byrow=T)

    if (plot) {
        Plot(graph, layout)
    }

    graph
}

Random <- function(plot = T) {
    Process(RandomForR())
}
