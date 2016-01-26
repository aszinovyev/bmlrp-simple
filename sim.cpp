#include "stable.h"
#include "myassert.h"
#include "graph.h"
#include "bmlrp.h"
#include "misc.h"
#include "sim.h"


Network GetNetworkLevel(const Network& net_level0, int level) {
    return Network( GetLevel(net_level0.graph, net_level0.addrs, level),
                    net_level0.addrs, net_level0.points);
}

Addr S(Addr a, char s) {
    uniform_int_distribution<Addr> dist(0, ~((Addr)-1 << s));
    return (a << s) + dist(Gen);
}

// to [0,1] x [0,1]
void ScalePoints(vector<Point>& points) {
    myassert(!points.empty());

    float minx = points[0].x;
    float maxx = points[0].x;
    float miny = points[0].y;
    float maxy = points[0].y;

    for (uint i = 0; i < points.size(); ++i) {
        float x = points[i].x;
        float y = points[i].y;

        if (x < minx) {
            minx = x;
        }
        if (x > maxx) {
            maxx = x;
        }
        if (y < miny) {
            miny = y;
        }
        if (y > maxy) {
            maxy = y;
        }
    }

    for (uint i = 0; i < points.size(); ++i) {
        points[i].x = (points[i].x - minx) / (maxx - minx);
        points[i].y = (points[i].y - miny) / (maxy - miny);
    }
}

float Sqr(float a) {
    return a*a;
}

bool Close(Point a, Point b, float r) {
    return Sqr(a.x - b.x) + Sqr(a.y - b.y) <= Sqr(r);
}

Network Random(int n, float r_coeff) {
    float r = r_coeff / sqrt(n);

    uniform_int_distribution<Addr> distAddr;
    uniform_real_distribution<float> distFloat;

    vector<Addr> addrs(n);
    vector<Point> points(n);

    for (int i = 0; i < n; ++i) {
        addrs[i] = distAddr(Gen);

        points[i].x = distFloat(Gen);
        points[i].y = distFloat(Gen);
    }
    ScalePoints(points);

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

    vector<Addr> addrs = { S(0,0), S(1,29), S(3,30), S(1,30), S(2,30) };

    vector<Point> points = {Point(1, 1), Point(2, 1), Point(1, 0), Point(0, 0), Point(0, 1)};
    ScalePoints(points);

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

    vector<Addr> addrs = { S(1,31), S(0,31), S(0,31), S(0,31), S(1,31), S(1,31) };

    vector<Point> points = { Point(0,1), Point(1,1), Point(2,1), Point(3,1),
                             Point(4,1), Point(2,0)
                           };
    ScalePoints(points);

    return Network(graph, addrs, points);
}

Network Manual2() {
    Graph graph(14);
    graph.edges[0] = {1};
    graph.edges[1] = {0,2};
    graph.edges[2] = {1,3};
    graph.edges[3] = {2,4};
    graph.edges[4] = {3,5,9};
    graph.edges[5] = {4,6};
    graph.edges[6] = {5,7,10};
    graph.edges[7] = {6,8};
    graph.edges[8] = {7};
    graph.edges[9] = {4,11};
    graph.edges[10] = {6,12};
    graph.edges[11] = {9,13};
    graph.edges[12] = {10,13};
    graph.edges[13] = {11,12};

    vector<Addr> addrs = { S(1,31), S(0,0), S(1,27), S(2,27),
                           S(3,27), S(4,27), S(5,27), S(6,27), //S(7,29),
                           S(5,29), S(7,27), S(8,27), S(9,27),
                           S(10,27), S(6,29)
                         };

    vector<Point> points = { Point(0,3), Point(1,3), Point(2,3), Point(3,3),
                             Point(4,3), Point(5,3), Point(6,3), Point(7,3),
                             Point(8,3), Point(4,2), Point(5.33,2), Point(4,1),
                             Point(4.66,1), Point(4,0)
                           };
    ScalePoints(points);

    return Network(graph, addrs, points);
}

Network Manual3() {
    Graph graph(9);
    graph.edges[0] = {1};
    graph.edges[1] = {0,2,3};
    graph.edges[2] = {1,5};
    graph.edges[3] = {1,4};
    graph.edges[4] = {3,5};
    graph.edges[5] = {2,4,6};
    graph.edges[6] = {5,7};
    graph.edges[7] = {6,8};
    graph.edges[8] = {7};

    vector<Addr> addrs = { S(1,31), S(1,28), S(2,28), S(5,29),
                           S(4,28), S(5,28), S(6,28), S(0,31),
                           S(6,29)
                         };

    vector<Point> points = { Point(0,2), Point(0.5,1), Point(1.5,1), Point(0,0),
                             Point(1,0), Point(2,0), Point(3,0), Point(4,-1),
                             Point(5,-1)
                           };
    ScalePoints(points);

    return Network(graph, addrs, points);
}

Network Manual4() {
    Graph graph(10);
    graph.edges[0] = {1};
    graph.edges[1] = {0,2,3};
    graph.edges[2] = {1,5};
    graph.edges[3] = {1,4};
    graph.edges[4] = {3,5,9};
    graph.edges[5] = {2,4,6};
    graph.edges[6] = {5,7};
    graph.edges[7] = {6,8};
    graph.edges[8] = {7};
    graph.edges[9] = {4};

    vector<Addr> addrs = { S(4,29), S(1,28), S(2,28), S(5,29),
                           S(4,28), S(5,28), S(6,28), S(0,31),
                           S(7,29), S(4,29)
                         };

    vector<Point> points = { Point(0,2), Point(0.5,1), Point(1.5,1), Point(0,0),
                             Point(1,0), Point(2,0), Point(3,0), Point(4,-1),
                             Point(5,-1), Point(0.5,-1)
                           };
    ScalePoints(points);

    return Network(graph, addrs, points);
}
