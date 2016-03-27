#ifndef SIM_H
#define SIM_H

using namespace std;

class Point {
public:
    float x;
    float y;

    Point() {
        x = 0;
        y = 0;
    }

    Point(float x, float y) {
        Point::x = x;
        Point::y = y;
    }
};

class Network {
public:
    Graph graph;
    vector<Addr> addrs;
    vector<Point> points;

    Network() {}

    Network(Graph graph, vector<Addr> addrs, vector<Point> points) {
        Network::graph = graph;
        Network::addrs = addrs;
        Network::points = points;
    }
};


Network GetNetworkLevel(const Network& net_level0, int level);

Network Random(int n, float r_coeff, float random_edges_ratio_nodes);
vector<float> GetAverageNodeDegrees(const Network& net_level0, uint max_level);

Network Overlay(int n, float deg);
Network Manual0();
Network Manual1();
Network Manual2();
Network Manual3();
Network Manual4();
Network Manual5();

#endif // SIM_H
