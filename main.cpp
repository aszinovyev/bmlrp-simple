#include "stable.h"
#include "myassert.h"
#include "graph.h"
#include "bmlrp.h"
#include "misc.h"
#include "sim.h"

using namespace std;

int main() {
    Network net = Manual0();

    Graph graph = net.graph;
    vector<Addr> addrs = net.addrs;
    vector<Point> points = net.points;

    for (uint i = 0; i < addrs.size(); ++i) {
        cout << Binary(addrs[i]) << endl;
    }
    cout << endl;

//    for (uint i = 0; i < points.size(); ++i) {
//        cout << points[i].x << " " << points[i].y << endl;
//    }
//    cout << endl;

    graph.Print();
    cout << endl;
    GetLevel(graph, addrs, 1).Print();

//    const int n = 10;

//    Graph graph;
//    vector<Addr> addrs;
//    vector<Point> points;

//    tie(graph, addrs, points) = Random(n, 10, 3.7);

//    for (int i = 0; i < n; ++i) {
//        cout << i << ": ";

//        for (uint j = 0; j < graph.edges[i].size(); ++j) {
//            cout << graph.edges[i][j] << " ";
//        }

//        cout << " |  " << Binary(addrs[i], 4) << "  |  " << points[i].x << " " << points[i].y << endl;
//    }

    return 0;
}
