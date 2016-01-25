require(Rcpp)
require(igraph)

Sys.setenv("PKG_CXXFLAGS"="-std=c++11")

sourceCpp("export.cpp")

Process <- function(data, draw, use_layout, ...) {
    labels <- data$labels
    colors <- ifelse(data$colors, "gray75", "white")
    n = length(colors)

    graph <- graph(edges = data$edges + 1, n = n, directed = F)

    cat("Average node degree:", ecount(graph) * 2 / n, "\n\n")

    if (draw) {
        ratio <- 16/9
        layout <- NULL
        if (use_layout) {
            layout <- matrix(data$coords, ncol=2, byrow=T)
            layout[, 1] <- (layout[, 1] * 2 - 1) * ratio
            layout[, 2] <- layout[, 2] * 2 - 1
        } else {
            layout <- layout.auto(graph)
            layout <- layout.norm(layout, -ratio, ratio, -1, 1)   # adjusting for 16:9 display
        }

        plot( graph, vertex.label = labels, vertex.label.color = "black", vertex.color = colors, 
              layout = layout, rescale = F, ... )
    }

    graph
}

Random <- function(n, r_coeff, level = 0, filter = "", labelLen = 0, draw = T, layout = T, ...) {
    Process(Random_R(n, r_coeff, level, filter, labelLen), draw, layout, ...)
}

Manual0 <- function(level = 0, draw = T, layout = T) {
    Process(Manual0_R(level, 3), draw, layout)
}

Manual1 <- function(level = 0, draw = T, layout = T) {
    Process(Manual1_R(level, 3), draw, layout)
}
