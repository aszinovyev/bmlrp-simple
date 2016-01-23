#include <vector>
#include <tuple>
#include <random>
#include "bmlrp.h"
#include "sim.h"

float Sqr(float a) {
    return a*a;
}

bool Close(Point a, Point b, float r) {
    return Sqr(a.x - b.x) + Sqr(a.y - b.y) <= Sqr(r);
}

tuple< Graph, vector<Addr>, vector<Point> > Random(int n, float sz, float r) {
    default_random_engine gen;
    uniform_int_distribution<Addr> distAddr;
    uniform_real_distribution<float> distFloat(0, sz);

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

    return make_tuple(res, addrs, points);
}
