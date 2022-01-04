#ifndef _TRI_H_
#define _TRI_H_

#include "base.h"
#include "bitmap.h"
#include <cmath>

using namespace std;

class Tri : public Base {
public:
    Tri(const Point& _a, const Point& _b, const Point& _c, const RGB& _color): Base(a, _color), a(_a), b(_b), c(_c) {}
    
    void draw(Bitmap& map, char method) const {
        map.drawSolidTriangle(a, b, c, getColor(), method);
    }

    Base* copy() const {
        Base* p = new Tri(a, b, c, getColor());
        return p;
    }

    void operator*=(double scale) {
        b = Point(a.getX() + int((b.getX() - a.getX())*scale), a.getY() + int((b.getY() - a.getY())*scale));
        c = Point(a.getX() + int((c.getX() - a.getX())*scale), a.getY() + int((c.getY() - a.getY())*scale));
    }
private:
    Point a, b, c;
};

#endif // _TRI_H_
