#ifndef SIM_H
#define SIM_H

using namespace std;

struct Point {
    float x;
    float y;
};

tuple< Graph, vector<Addr>, vector<Point> > Random(int n, float sz, float r);

#endif // SIM_H
