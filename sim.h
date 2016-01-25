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

typedef tuple< Graph, vector<Addr>, vector<Point> > GraphInfo;


GraphInfo Random(int n, float sz, float r);
GraphInfo Manual0();
GraphInfo Manual1();
GraphInfo Manual2();

#endif // SIM_H
