#ifndef EXPORT_H
#define EXPORT_H

class Network_R {
public:
    vector<uint> edges;
    vector<string> labels;
    vector<bool> colors;
    vector<float> coords;   //x1,y1,x2,y2,...

    Network_R() {}

    Network_R(const Network& net, const string& filter, int labelLen) {
        Graph graph = net.graph;
        vector<Addr> addrs = net.addrs;
        vector<Point> points = net.points;

        const uint n = net.graph.n;

        myassert(addrs.size() == n);
        myassert(points.size() == n);

        int include[n];
        int j = 0;
        for (uint i = 0; i < n; ++i) {
            if (IncludeAddr(addrs[i], filter)) {
                include[i] = j++;
            } else {
                include[i] = -1;
            }
        }

        edges = Edges_R(graph, include);

        for (uint i = 0; i < n; ++i) {
            if (include[i] != -1) {
                labels.push_back( Binary(addrs[i], labelLen, false) );
                colors.push_back( addrs[i] & (FirstBit >> filter.size()) );
                coords.push_back( points[i].x );
                coords.push_back( points[i].y );
            }
        }
    }

private:
    bool IncludeAddr(Addr a, const string& filter) {
        for (uint i = 0; i < filter.size(); ++i) {
            char ch = filter[i] - '0';
            myassert(ch == 0 || ch == 1);

            if ((bool)(a & FirstBit) != ch) {
                return false;
            }

            a <<= 1;
        }

        return true;
    }

    vector<uint> Edges_R(Graph graph, int* include) {
        vector<uint> res;

        for (uint i = 0; i < graph.n; ++i) {
            for (uint j = 0; j < graph.edges[i].size(); ++j) {
                uint to = graph.edges[i][j];

                if ((to > i) && (include[i] != -1) && (include[to] != -1)) {
                    res.push_back(include[i]);
                    res.push_back(include[to]);
                }
            }
        }

        return res;
    }
};

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

#endif // EXPORT_H
