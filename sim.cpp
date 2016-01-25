#include "stable.h"
#include "graph.h"
#include "bmlrp.h"
#include "sim.h"


Network GetNetworkLevel(const Network& net_level0, int level) {
    return Network( GetLevel(net_level0.graph, net_level0.addrs, level),
                    net_level0.addrs, net_level0.points);
}

float Sqr(float a) {
    return a*a;
}

bool Close(Point a, Point b, float r) {
    return Sqr(a.x - b.x) + Sqr(a.y - b.y) <= Sqr(r);
}

Network Random(int n, float r_coeff) {
    float r = r_coeff / sqrt(n);

    default_random_engine gen;
    gen.seed(n);
    uniform_int_distribution<Addr> distAddr;
    uniform_real_distribution<float> distFloat;

    vector<Addr> addrs(n);
    vector<Point> points(n);

    for (int i = 0; i < n; ++i) {
        addrs[i] = distAddr(gen);

        points[i].x = distFloat(gen);
        points[i].y = distFloat(gen);
    }

    Graph res(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if ( (i != j) && Close(points[i], points[j], r) ) {
                res.edges[i].push_back(j);
            }
        }
    }

    return Network(res, addrs, points);
}

Network Manual0() {
    Graph graph(5);
    graph.edges[0] = {1,2,4};
    graph.edges[1] = {0};
    graph.edges[2] = {0,3};
    graph.edges[3] = {2,4};
    graph.edges[4] = {3,0};

    vector<Addr> addrs = {0, (Addr)1 << 29, (Addr)(3 << 30), (Addr)(1 << 30), (Addr)(2 << 30)};

    vector<Point> points = {Point(1, 1), Point(2, 1), Point(1, 0), Point(0, 0), Point(0, 1)};

    return Network(graph, addrs, points);
}

Network Manual1() {
    Graph graph(6);
    graph.edges[0] = {1};
    graph.edges[1] = {0,2};
    graph.edges[2] = {1,3,5};
    graph.edges[3] = {2,4};
    graph.edges[4] = {3};
    graph.edges[5] = {2};

    vector<Addr> addrs = {FirstBit, 0, (Addr)1 << 29, (Addr)1 << 30, (Addr)5 << 29, (Addr)3 << 30};

    vector<Point> points = {Point(0, 1), Point(1, 1), Point(2, 1), Point(3, 1), Point(4, 1), Point(2, 0)};

    return Network(graph, addrs, points);
}
