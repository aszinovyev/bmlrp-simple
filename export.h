#ifndef EXPORT_H
#define EXPORT_H

struct GraphR {
    vector<int> edges;
    vector<string> labels;
    vector<bool> colors;
    vector<float> coords;   //x1,y1,x2,y2,...
};

RCPP_EXPOSED_CLASS(GraphR)

RCPP_MODULE(md) {
    using namespace Rcpp;

    class_<GraphR>("Graph")
        .constructor()

        .field("edges", &GraphR::edges)
        .field("labels", &GraphR::labels)
        .field("colors", &GraphR::colors)
        .field("coords", &GraphR::coords)

        ;
}

#endif // EXPORT_H
