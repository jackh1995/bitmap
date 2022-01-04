#ifndef _BASE_H_
#define _BASE_H_

#include "bitmap.h"
#include "point.h"
#include "rgb.h"

#include <ctime>


class Base {

public:

Base() : count(1) {}
Base(const Point& _anchor, const RGB& _color)
: count(1), anchor(_anchor), color(_color) {}

virtual ~Base() {}
virtual Base* copy() const = 0;

// Getters
Point getAnchor() const {
    return anchor;
}
RGB getColor() const {
    return color;
}

// Drawing methods
virtual void draw(Bitmap& map, char method) const = 0;

// Setters

void setColor(const RGB& _color) {
    color = _color;
}


void setColor() {
    color = RGB(rand()%255, rand()%255, rand()%255);

}

void operator+=(const Point& displacement) {
    anchor += displacement;
}

virtual void operator*=(double scale) = 0;

int count;
private:
    Point anchor;
    RGB color;
};


#endif