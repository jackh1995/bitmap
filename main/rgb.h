#ifndef _RGB_H_
#define _RGB_H_

class RGB {
public:
    RGB(unsigned char _r=0, unsigned char _g=0, unsigned char _b=0) : r(_r), g(_g), b(_b) {}
    RGB operator+(const RGB& other) {
        return RGB(other.getR(), other.getG(), other.getB());
    }
    RGB& operator+=(const RGB& other) {
        r += other.r;
        g += other.g;
        b += other.b;
        return *this;
    }
    unsigned char getR() const {
        return r;
    }
    unsigned char getG() const {
        return g;
    }
    unsigned char getB() const {
        return b;
    }
    friend ostream& operator<<(ostream& os, const RGB& rgb) {
        os << "RGB(" << int(rgb.getR()) << ", " << int(rgb.getG()) << ", " << int(rgb.getB()) << ')';
        return os;
    }
private:
    unsigned char r, g, b;
};

#endif // _RGB_H_