#ifndef EXPORT_H
#define EXPORT_H

class GraphWrapper {
public:
    vector<uint> edges;
    vector<string> labels;
    vector<bool> colors;
    vector<float> coords;   //x1,y1,x2,y2,...

    GraphWrapper() {}

    GraphWrapper(GraphInfo graphInfo, int format) {
        Graph graph;
        vector<Addr> addrs;
        vector<Point> points;
        tie(graph, addrs, points) = graphInfo;

        edges = EdgesForR(graph);
        labels.resize(graph.n);
        colors.resize(graph.n);
        coords.resize(graph.n * 2);

        for (int i = 0; i < graph.n; ++i) {
            labels[i] = Binary(addrs[i], format, false);
            colors[i] = (addrs[i] & FirstBit);
            coords[i*2] = points[i].x;
            coords[i*2+1] = points[i].y;
        }
    }

    vector<uint> EdgesForR(Graph graph) {
        vector<uint> res;
        for (uint i = 0; i < graph.n; ++i) {
            for (uint j = 0; j < graph.edges[i].size(); ++j) {
                uint to = graph.edges[i][j];

                if (to > i) {
                    res.push_back(i);
                    res.push_back(to);
                }
            }
        }

        return res;
    }
};

RCPP_EXPOSED_CLASS(GraphWrapper)

RCPP_MODULE(md) {
    using namespace Rcpp;

    class_<GraphWrapper>("Graph")
        .constructor()

        .field("edges", &GraphWrapper::edges)
        .field("labels", &GraphWrapper::labels)
        .field("colors", &GraphWrapper::colors)
        .field("coords", &GraphWrapper::coords)

        ;
}

#endif // EXPORT_H
