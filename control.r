require(Rcpp)
require(igraph)

Sys.setenv("PKG_CXXFLAGS"="-std=c++11")
sourceCpp("export.cpp")


ResetSeed <- function() {
    Seed <<- 0xFA2B5E01
}
SetSeed <- function(seed) {
    Seed <<- seed
}
if (!exists("Seed")) {
    ResetSeed()
}


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

Random <- function(n, r_coeff, random_edges_ratio_nodes = 0, 
                   level = 0, filter = "", label = 0, draw = T, layout = T, ...) 
{
    SetSeed_R(Seed)
    Process(Random_R(n, r_coeff, random_edges_ratio_nodes, level, filter, label), draw, layout, ...)
}

RandomNodeDegrees <- function(n, r_coeff, random_edges_ratio_nodes = 0, max_level = 0) {
    SetSeed_R(Seed)
    RandomNodeDegrees_R(n, r_coeff, random_edges_ratio_nodes, max_level)
}

Manual0 <- function(level = 0, filter = "", draw = T, layout = T) {
    SetSeed_R(Seed)
    Process(Manual0_R(level, filter), draw, layout)
}

Manual1 <- function(level = 0, filter = "", draw = T, layout = T) {
    SetSeed_R(Seed)
    Process(Manual1_R(level, filter), draw, layout)
}

Manual2 <- function(level = 0, filter = "", draw = T, layout = T) {
    SetSeed_R(Seed)
    Process(Manual2_R(level, filter), draw, layout)
}

Manual3 <- function(level = 0, filter = "", draw = T, layout = T) {
    SetSeed_R(Seed)
    Process(Manual3_R(level, filter), draw, layout)
}

Manual4 <- function(level = 0, filter = "", draw = T, layout = T) {
    SetSeed_R(Seed)
    Process(Manual4_R(level, filter), draw, layout)
}

Manual5 <- function(level = 0, filter = "", draw = T, layout = T) {
    SetSeed_R(Seed)
    Process(Manual5_R(level, filter), draw, layout)
}
