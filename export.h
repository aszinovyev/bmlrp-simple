#ifndef EXPORT_H
#define EXPORT_H

class Network_R {
public:
    std::vector<int> edges;
    std::vector<std::string> labels;
    std::vector<bool> colors;
    std::vector<float> coords;   //x1,y1,x2,y2,...

    Network_R() {}

    Network_R(const Network& net, const std::string& filter, char label) {
        Graph graph = net.graph;
        std::vector<Addr> addrs = net.addrs;
        std::vector<Point> points = net.points;

        const int n = net.graph.n;

        myassert(addrs.size() == n);
        myassert(points.size() == n);

        int include[n];
        int j = 0;
        for (int i = 0; i < n; ++i) {
            if (IncludeAddr(addrs[i], filter)) {
                include[i] = j++;
            } else {
                include[i] = -1;
            }
        }

        edges = Edges_R(graph, include);

        for (int i = 0; i < n; ++i) {
            if (include[i] != -1) {
                if (label < 0) {
                    labels.push_back( std::to_string(i) );
                } else {
                    labels.push_back( Binary(addrs[i], label, false) );
                }

                colors.push_back( addrs[i] & (Msb >> filter.size()) );

                coords.push_back( points[i].x );
                coords.push_back( points[i].y );
            }
        }
    }

private:
    bool IncludeAddr(Addr a, const std::string& filter) {
        for (uint i = 0; i < filter.size(); ++i) {
            char ch = filter[i] - '0';
            myassert(ch == 0 || ch == 1);

            if ((bool)(a & Msb) != ch) {
                return false;
            }

            a <<= 1;
        }

        return true;
    }

    std::vector<int> Edges_R(Graph graph, int* include) {
        std::vector<int> res;

        for (int i = 0; i < graph.n; ++i) {
            std::vector<int> succ = graph.GetDirectSuccessors(i);

            for (uint j = 0; j < succ.size(); ++j) {
                int to = succ[j];

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
