require(Rcpp)
require(igraph)

Sys.setenv("PKG_CXXFLAGS"="-std=c++11")

sourceCpp("export.cpp")

Plot <- function(graph, layout) {
    plot(graph, vertex.label = V(graph)$names, vertex.label.color = "black", vertex.color = V(graph)$colors, layout = layout)
}

Process <- function(data, draw, use_layout) {
    labels <- data$labels
    colors <- ifelse(data$colors, "gray75", "white")

    layout <- matrix(data$coords, ncol=2, byrow=T)

    n = length(colors)

    graph <- graph(edges = data$edges + 1, n = n, directed = F)

    cat("Average node degree:", ecount(graph) * 2 / n, "\n")

    if (draw) {
        if (use_layout) {
            plot(graph, vertex.label = labels, vertex.label.color = "black", vertex.color = colors, layout = layout)
        } else {
            plot(graph, vertex.label = labels, vertex.label.color = "black", vertex.color = colors)
        }

    }

    graph
}

Random <- function(level = 0, format = 5, draw = T, layout = T) {
    Process(Random_R(level, format), draw, layout)
}

Manual0 <- function(level = 0, format = 3, draw = T, layout = T) {
    Process(Manual0_R(level, format), draw, layout)
}
