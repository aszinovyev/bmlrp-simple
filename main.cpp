#include <iostream>
#include <vector>
#include <set>
#include <tuple>
#include "misc.h"
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

        for (auto it = graph.edges.lower_bound(make_pair(i, 0));
             it != graph.edges.end() && it->first == i; ++it)
        {
            cout << it->second << " ";
        }

        cout << " |  " << Binary(addrs[i], 4) << "  |  " << points[i].x << " " << points[i].y << endl;
    }

    return 0;
}
