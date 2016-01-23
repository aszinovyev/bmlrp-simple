#include <iostream>
#include <vector>
#include <tuple>
#include "misc.h"
#include "graph.h"
#include "bmlrp.h"
#include "sim.h"

using namespace std;

int main() {
    const int n = 10;

    Graph graph;
    vector<Addr> addrs;
    vector<Point> points;

    tie(graph, addrs, points) = Random(n, 10, 3.7);

    for (int i = 0; i < n; ++i) {
        cout << i << ": ";

        for (uint j = 0; j < graph.edges[i].size(); ++j) {
            cout << graph.edges[i][j] << " ";
        }

        cout << " |  " << Binary(addrs[i], 4) << "  |  " << points[i].x << " " << points[i].y << endl;
    }

    return 0;
}
