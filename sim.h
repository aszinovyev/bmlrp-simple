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

tuple< Graph, vector<Addr>, vector<Point> > Random(int n, float sz, float r);
tuple< Graph, vector<Addr>, vector<Point> > Manual0();

#endif // SIM_H
