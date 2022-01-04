#ifndef _HANDLE_H_
#define _HANDLE_H_


#include "circle.h"
#include "rect.h"
#include "tri.h"

class Handle {

public:

// Constructors
Handle() : p(NULL) {}
// Circle
Handle(const Point& center, int radius, const RGB& color) {
    p = new Circle(center, radius, color);
}
// Tri
Handle(const Point& a, const Point& b, const Point& c, const RGB& color) {
    p = new Tri(a, b, c, color);
}
// Rect
Handle(const Point& base, int width, int height, const RGB& color) {
    p = new Rect(base, width, height, color);
}

// Rule of three
// 1. Copy constructor
Handle(const Handle& h) {
    p = h.p;
}
// 2. Copier
Handle& operator=(const Handle& h) {
    if (p!=NULL && --(p->count) == 0)
        delete p;
    p = h.p;
    ++(p->count);
    return *this;
}
// 3. Destructor
~Handle() {
    if (p!=NULL && --(p->count) == 0)
        delete p;
}

void draw (Bitmap& map, int method) const {
    p->draw(map, method);
}

// Copy on write

// Set color
void setColor(const RGB& color) {
    if (p->count == 1)
        p->setColor(color);
    else {
        --(p->count);
        p = p->copy();
        p->setColor(color);
    }
}
void setColor() {
    if (p->count == 1)
        p->setColor();
    else {
        --(p->count);
        p = p->copy();
        p->setColor();
    }
}

// Shift
Handle& operator+=(const Point& displacement) {
    if (p->count == 1)
        (*p) += displacement;
    else {
        --(p->count);
        p = p->copy();
        (*p) += displacement;
    }
    return *this;
}

Handle operator+(const Point& displacement) {
    Base *result = p->copy();
    (*result) += displacement;
    return Handle(result);
}

// Scale
Handle& operator*=(double scale) {
    if (p->count == 1) 
        (*p) *= scale;
    else {
        --(p->count);
        p = p->copy();
        (*p) *= scale;
    }
    return *this;
}
Handle operator*(double scale) {
    Base* result = p->copy();
    (*result) *= scale;
    return Handle(result);
}

private:
Base *p;
Handle(Base *_p): p(_p) {}
};


#endif // _HANDLE_H_
