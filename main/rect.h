#ifndef _RECT_H_
#define _RECT_H_

#include "base.h"
#include "bitmap.h"

using namespace std;


class Rect : public Base {
public:
    Rect(const Point _base, int _width, int _height, RGB _color)
    :Base(_base, _color), width(_width), height(_height) {}
    
    void draw(Bitmap& map, char method) const {
        map.drawSolidRect(getAnchor(), width, height, getColor(), method);
    }

    Base* copy() const {
        Base* p = new Rect(getAnchor(), width, height, getColor());
        return p;
    }

    void operator*=(double scale) {
        width = int(width * scale);
        height = int(height * scale);
    }

private:
    int width;
    int height;
};

#endif // _RECT_H_
