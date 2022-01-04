#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
using namespace std;
class Point {
public:
    Point(int _x=0, int _y=0) : x(_x), y(_y) {}
    Point operator+(const Point& other) const {
        return Point(this->x + other.x, this->y + other.y);
    }
    Point& operator+=(const Point& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    friend ostream& operator<<(ostream& os, const Point& p) {
        os << "Point(" << p.getX() << ", " << p.getY() << ')';
        return os;
    }
    int getX() const {
        return x;
    }
    int getY() const {
        return y;
    }

private:
    int x;
    int y;
};

#endif // _POINT_H