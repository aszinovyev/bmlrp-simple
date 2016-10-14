#include <iostream>
#include <vector>

#include "bmlrp.h"
#include "debug.h"
#include "graph.h"
#include "misc.h"
#include "sim.h"

using std::cout;
using std::endl;

int main() {
  Gen.seed(2);
  std::vector<float> node_degrees =
      GetAverageNodeDegrees(Random(1<<18, 2.3, 0.1), 20);

  for (uint i = 0; i < node_degrees.size(); ++i) {
    cout << node_degrees[i] << ",  ";
  }
  cout << endl;

  //    Gen.seed(0xFA2B5E01);
  //    Network net = Random(1<<15, 2.3, 0);
  //    GetLevel(net.graph, net.addrs, 20);

  //    Gen.seed(3097);
  //    Network net = Random(13, 2, 0);

  //    Gen.seed(426);
  //    Network net = Random(6, 2, 0);

  //    for (uint i = 0; i < net.addrs.size(); ++i) {
  //        cout << i << "  " << Binary(net.addrs[i]) << endl;
  //    }
  //    cout << endl;

  //    for (uint i = 0; i < net.points.size(); ++i) {
  //        cout << net.points[i].x << " " << net.points[i].y << endl;
  //    }
  //    cout << endl;

  //    for (int i = 0; i <= 5; ++i) {
  //        PrintGraph(GetLevel(net.graph, net.addrs, i));
  //        cout << endl;
  //    }

  return 0;
}
