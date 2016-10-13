#include "stable.h"
#include "misc.h"
#include "graph.h"
#include "bmlrp.h"
#include "test.h"
#include "debug.h"
#include "sim.h"

using std::cout;
using std::cerr;
using std::endl;
using std::uniform_int_distribution;
using std::uniform_real_distribution;

Network GetNetworkLevel(const Network& net_level0, int level) {
    return Network( GetLevel(net_level0.graph, net_level0.addrs, level),
                    net_level0.addrs, net_level0.points);
}

std::vector<float> GetAverageNodeDegrees(const Network& net_level0, int max_level) {
    myassert(max_level <= (int)sizeof(Addr) * 8);
    myassert(IsGraphConnected(net_level0.graph));

    Graph graph = net_level0.graph;

    std::vector<float> res;
    res.push_back( (float)graph.edges.size() / graph.n );

    std::vector<Addr> addrs_copy = net_level0.addrs;

    for (int level_i = 1; level_i <= max_level; ++level_i) {
        graph = NextLevel(graph, addrs_copy);
        TestNextLevel(graph, net_level0.addrs, level_i);

        res.push_back( (float)graph.edges.size() / graph.n );

        for (uint i = 0; i < addrs_copy.size(); ++i) {
            addrs_copy[i] <<= 1;
        }
    }

    return res;
}

Addr GenAddr(Addr prefix, uchar prefix_len = 1) {
    uniform_int_distribution<Addr> dist(0, ((Addr)-1) >> prefix_len);
    return (prefix << (sizeof(prefix)*8 - prefix_len)) + dist(Gen);
}

Addr GenAddr() {
    uniform_int_distribution<Addr> dist;
    return dist(Gen);
}

// to [0,1] x [0,1]
void ScalePoints(std::vector<Point>& points) {
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

Network Random(int n, float r_coeff, float random_edges_ratio_nodes) {
    cerr << "Generating graph" << endl;

    const float r = r_coeff / sqrt(n);
    const int random_edges = n * random_edges_ratio_nodes / 2;

    uniform_real_distribution<float> distFloat;
    uniform_int_distribution<int> distInt;

    std::vector<Addr> addrs(n);
    std::vector<Point> points(n);

    for (int i = 0; i < n; ++i) {
        addrs[i] = GenAddr();

        points[i].x = distFloat(Gen);
        points[i].y = distFloat(Gen);
    }

    Graph res(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if ( (i != j) && Close(points[i], points[j], r) ) {
                res.AddEdge(i, j);
            }
        }
    }

    ScalePoints(points);

    for (int i = 0; i < random_edges; ++i) {
        int a = distInt(Gen) % n;
        int b = distInt(Gen) % n;
        myassert(a >= 0 && b >= 0);

        if (a != b) {
            res.AddEdgeBidirectional(a, b);
        }
    }

    return Network(res, addrs, points);
}

Network Manual0() {
    Graph graph(5);
    graph.AddEdgeBidirectional(0, 1);
    graph.AddEdgeBidirectional(0, 2);
    graph.AddEdgeBidirectional(0, 4);
    graph.AddEdgeBidirectional(2, 3);
    graph.AddEdgeBidirectional(3, 4);

    std::vector<Addr> addrs = { GenAddr(0), GenAddr(0), GenAddr(1), GenAddr(0), GenAddr(1) };

    std::vector<Point> points = {{1, 1}, {2, 1}, {1, 0}, {0, 0}, {0, 1}};
    ScalePoints(points);

    return Network(graph, addrs, points);
}

Network Manual1() {
    Graph graph(6);
    graph.AddEdgeBidirectional(0, 1);
    graph.AddEdgeBidirectional(1, 2);
    graph.AddEdgeBidirectional(2, 3);
    graph.AddEdgeBidirectional(2, 5);
    graph.AddEdgeBidirectional(3, 4);

    std::vector<Addr> addrs = { GenAddr(1), GenAddr(0), GenAddr(0), GenAddr(0),
                           GenAddr(1), GenAddr(1)
                         };

    std::vector<Point> points = {{0,1}, {1,1}, {2,1}, {3,1}, {4,1}, {2,0}};
    ScalePoints(points);

    return Network(graph, addrs, points);
}

Network Manual2() {
    Graph graph(14);
    graph.AddEdgeBidirectional(0, 1);
    graph.AddEdgeBidirectional(1, 2);
    graph.AddEdgeBidirectional(2, 3);
    graph.AddEdgeBidirectional(3, 4);
    graph.AddEdgeBidirectional(4, 5);
    graph.AddEdgeBidirectional(4, 9);
    graph.AddEdgeBidirectional(5, 6);
    graph.AddEdgeBidirectional(6, 7);
    graph.AddEdgeBidirectional(6, 10);
    graph.AddEdgeBidirectional(7, 8);
    graph.AddEdgeBidirectional(9, 11);
    graph.AddEdgeBidirectional(10, 12);
    graph.AddEdgeBidirectional(11, 13);
    graph.AddEdgeBidirectional(12, 13);

    std::vector<Addr> addrs = { GenAddr(1), GenAddr(0), GenAddr(0), GenAddr(0),
                           GenAddr(0), GenAddr(0), GenAddr(0), GenAddr(0), //GenAddr(1),
                           GenAddr(1), GenAddr(0), GenAddr(0), GenAddr(0),
                           GenAddr(0), GenAddr(1)
                         };

    std::vector<Point> points = {{0,3}, {1,3}, {2,3}, {3,3},
                                 {4,3}, {5,3}, {6,3}, {7,3},
                                 {8,3}, {4,2}, {5.33,2}, {4,1},
                                 {4.66,1}, {4,0}};
    ScalePoints(points);

    return Network(graph, addrs, points);
}

Network Manual3() {
    Graph graph(9);
    graph.AddEdgeBidirectional(0, 1);
    graph.AddEdgeBidirectional(1, 2);
    graph.AddEdgeBidirectional(1, 3);
    graph.AddEdgeBidirectional(2, 5);
    graph.AddEdgeBidirectional(3, 4);
    graph.AddEdgeBidirectional(4, 5);
    graph.AddEdgeBidirectional(5, 6);
    graph.AddEdgeBidirectional(6, 7);
    graph.AddEdgeBidirectional(7, 8);

    std::vector<Addr> addrs = { GenAddr(1), GenAddr(0), GenAddr(0), GenAddr(1),
                           GenAddr(0), GenAddr(0), GenAddr(0), GenAddr(0),
                           GenAddr(1)
                         };

    std::vector<Point> points = {{0,2}, {0.5,1}, {1.5,1}, {0,0},
                                 {1,0}, {2,0}, {3,0}, {4,-1},
                                 {5,-1}};
    ScalePoints(points);

    return Network(graph, addrs, points);
}

Network Manual4() {
    Graph graph(10);
    graph.AddEdgeBidirectional(0, 1);
    graph.AddEdgeBidirectional(1, 2);
    graph.AddEdgeBidirectional(1, 3);
    graph.AddEdgeBidirectional(2, 5);
    graph.AddEdgeBidirectional(3, 4);
    graph.AddEdgeBidirectional(4, 5);
    graph.AddEdgeBidirectional(4, 9);
    graph.AddEdgeBidirectional(5, 6);
    graph.AddEdgeBidirectional(6, 7);
    graph.AddEdgeBidirectional(7, 8);

    std::vector<Addr> addrs = { GenAddr(1), GenAddr(0), GenAddr(0), GenAddr(1),
                           GenAddr(0), GenAddr(0), GenAddr(0), GenAddr(0),
                           GenAddr(1), GenAddr(1)
                         };


    std::vector<Point> points = {{0,2}, {0.5,1}, {1.5,1}, {0,0},
                                 {1,0}, {2,0}, {3,0}, {4,-1},
                                 {5,-1}, {0.5,-1}};
    ScalePoints(points);

    return Network(graph, addrs, points);
}

Network Manual5() {
    Graph graph(16);

    graph.AddEdgeBidirectional(0, 1);
    graph.AddEdgeBidirectional(1, 2);
    graph.AddEdgeBidirectional(2, 3);
    graph.AddEdgeBidirectional(4, 5);
    graph.AddEdgeBidirectional(5, 6);
    graph.AddEdgeBidirectional(6, 7);
    graph.AddEdgeBidirectional(8, 9);
    graph.AddEdgeBidirectional(9, 10);
    graph.AddEdgeBidirectional(10, 11);
    graph.AddEdgeBidirectional(12, 13);
    graph.AddEdgeBidirectional(13, 14);
    graph.AddEdgeBidirectional(14, 15);

    graph.AddEdgeBidirectional(0, 4);
    graph.AddEdgeBidirectional(1, 5);
    graph.AddEdgeBidirectional(2, 6);
    graph.AddEdgeBidirectional(3, 7);
    graph.AddEdgeBidirectional(4, 8);
    graph.AddEdgeBidirectional(5, 9);
    graph.AddEdgeBidirectional(6, 10);
    graph.AddEdgeBidirectional(7, 11);
    graph.AddEdgeBidirectional(8, 12);
    graph.AddEdgeBidirectional(9, 13);
    graph.AddEdgeBidirectional(10, 14);
    graph.AddEdgeBidirectional(11, 15);

    std::vector<Addr> addrs = { GenAddr(28, 5), GenAddr(12, 5), GenAddr(18, 5), GenAddr(25, 5),
                           GenAddr(17, 5), GenAddr(31, 5), GenAddr(10, 5), GenAddr(6, 5),
                           GenAddr(22, 5), GenAddr(11, 5), GenAddr(26, 5), GenAddr(9, 5),
                           GenAddr(27, 5), GenAddr(24, 5), GenAddr(7, 5), GenAddr(8, 5)
                         };
    cout << Binary(GenAddr(28, 5)) << endl;

    std::vector<Point> points = {{0,0}, {1,0}, {2,0}, {3,0},
                                 {0.1,1}, {1.1,1}, {2.1,1}, {3.1,1},
                                 {0,2}, {1,2}, {2,2}, {3,2},
                                 {0.1,3}, {1.1,3}, {2.1,3}, {3.1,3}};
    ScalePoints(points);

    return Network(graph, addrs, points);
}
