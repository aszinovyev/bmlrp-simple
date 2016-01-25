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

Network Random(int n, float r_coeff);
Network Manual0();
Network Manual1();
Network Manual2();

#endif // SIM_H
