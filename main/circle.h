#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "base.h"
#include "bitmap.h"

class Circle : public Base{
public:
    Circle(const Point& _center, int _radius, const RGB& _color)
    : Base(_center, _color), radius(_radius) {}

    void draw(Bitmap& map, char method) const {
        map.drawSolidCircle(this->getAnchor(), radius, this->getColor(), method);
    }

    Base* copy() const {
        Base* p = new Circle(getAnchor(), radius, getColor());
        return p;
    }

    void operator*=(double scale) {
        radius = int(radius * scale);
    }

private:
    int radius;
};

#endif // _CIRCLE_H_