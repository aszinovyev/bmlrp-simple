#include "stable.h"
#include "misc.h"
#include "graph.h"
#include "bmlrp.h"
#include "sim.h"
#include "debug.h"

using namespace std;

int main() {
    Gen.seed(3097);
    Network net = Random(13, 2);

//    Gen.seed(426);
//    Network net = Random(6, 2);

    Graph graph = net.graph;
    vector<Addr> addrs = net.addrs;
    vector<Point> points = net.points;

    for (uint i = 0; i < addrs.size(); ++i) {
        cout << i << "  " << Binary(addrs[i]) << endl;
    }
    cout << endl;

//    for (uint i = 0; i < points.size(); ++i) {
//        cout << points[i].x << " " << points[i].y << endl;
//    }
//    cout << endl;

    PrintGraph(graph);
    cout << endl;
    PrintGraph(GetLevel(graph, addrs, 1));

    return 0;
}
