
#ifndef _BITMAP_H_
#define _BITMAP_H_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

#include "point.h"
#include "rgb.h"

class Bitmap {
public:
    Bitmap(int _xSize, int _ySize) {
        xSize = _xSize;
        ySize = _ySize;
        image = (unsigned char *)calloc(3, (size_t) xSize * ySize);
    }

    ~Bitmap() {
        free(image);
    }

    void setPixel(const Point& p, const RGB& c, char m) {
        setPixel(p.getX(), p.getY(), c, m);
    }

    void setPixel(int x, int y, const RGB& c, char m) {
        unsigned char r, g, b;

        // x += xSize / 2;
        // y += ySize / 2;

        // Boundary check
        if (x<0 || y<0 || x>xSize || y>ySize) return;

        int offset = (y * xSize + x) * 3;
        b = image[offset];
        g = image[offset+1];
        r = image[offset+2];
        
        // Color manipulation
        switch (m) {
            case '+':
                b = (b <= 255-c.getB())? (unsigned char)(b+c.getB()): (unsigned char)(255);
                g = (g <= 255-c.getG())? (unsigned char)(g+c.getG()): (unsigned char)(255);
                r = (r <= 255-c.getR())? (unsigned char)(r+c.getR()): (unsigned char)(255);
                break;
            case '-':
                b = (b >= c.getB())? (unsigned char)(b-c.getB()): '\0';
                g = (g >= c.getG())? (unsigned char)(g-c.getG()): '\0';
                r = (r >= c.getR())? (unsigned char)(r-c.getR()): '\0';
                break;
            case '.':
                b = c.getB();
                g = c.getG();
                r = c.getR();
                break;
            default:
                break;
        }
        
        // Set the pixel
        image[offset]   = b;
        image[offset+1] = g;
        image[offset+2] = r;
    }

    void drawSolidCircle(Point center, int radius, RGB color, char method) {        
        int r2 = radius * radius;
        for (int x=-radius; x<=radius; ++x)
            for (int y=-radius; y<=radius; ++y)
                if (x*x+y*y <= r2)
                    setPixel(center+Point(x, y), color, method);
    }

    void drawSolidRect(Point base, int width, int height, RGB color, char method) {
        for (int x=0; x<=width; ++x) {
            for (int y=0; y<=height; ++y) {
                setPixel(base+Point(x, y), color, method);
            }
        }
    }

    
    int getTriArea(const Point& a, const Point& b, const Point& c) {
        return abs(a.getX() * (b.getY() - c.getY()) + b.getX() * (c.getY() - a.getY()) + c.getX() * (a.getY() - b.getY())) / 2;
    }

    bool triIsInterior(const Point& p, const Point& a, const Point& b, const Point& c) {
        if (getTriArea(a, b, c) == getTriArea(p, b, c) + getTriArea(a, p, c) + getTriArea(a, b, p))
            return true;
        else
            return false; 
    }
    void drawSolidTriangle(Point a, Point b, Point c, RGB color, char method) {
        int xMin, xMax, yMin, yMax;

        xMin = (a.getX() < b.getX())? a.getX() : b.getX();
        xMin = (xMin < c.getX())? xMin : c.getX();

        xMax = (a.getX() > b.getX())? a.getX() : b.getX();
        xMax = (xMax > c.getX())? xMax : c.getX();

        yMin = (a.getY() < b.getY())? a.getY() : b.getY();
        yMin = (yMin < c.getY())? yMin : c.getY();

        yMax = (a.getY() > b.getY())? a.getY() : b.getY();
        yMax = (yMax > c.getY())? yMax : c.getY();

        for (int x=xMin; x<=xMax; ++x) {
            for (int y=yMin; y<=yMax; ++y) {
                if (triIsInterior(Point(x, y), a, b, c))
                    setPixel(Point(x, y), color, method);
            }
        }
    }

    void setBackground(const RGB& color) {
        unsigned char r, g, b;
        for (int x=0; x<=xSize; ++x) {
            for (int y=0; y<=ySize; ++y) {
                int offset = (y * xSize + x) * 3;
                b = image[offset];
                g = image[offset+1];
                r = image[offset+2];
                if (b == '\0' && g == '\0' && r == '\0') {
                    setPixel(Point(x, y), color, '+');
                }
            }
        }
    }


    void clear() {
        memset(image, '\0', 3*xSize*ySize);
    }
    int save(const char* filename) const {
        unsigned char header[54] = {
            0x42, 0x4d, 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        long file_size = (long)xSize * (long)ySize * 3 + 54;
        header[2] = (unsigned char)(file_size &0x000000ff);
        header[3] = (file_size >> 8) & 0x000000ff;
        header[4] = (file_size >> 16) & 0x000000ff;
        header[5] = (file_size >> 24) & 0x000000ff;

        long width = xSize;
        header[18] = width & 0x000000ff;
        header[19] = (width >> 8) &0x000000ff;
        header[20] = (width >> 16) &0x000000ff;
        header[21] = (width >> 24) &0x000000ff;

        long height = ySize;
        header[22] = height &0x000000ff;
        header[23] = (height >> 8) &0x000000ff;
        header[24] = (height >> 16) &0x000000ff;
        header[25] = (height >> 24) &0x000000ff;

        FILE *fp;
        if (!(fp = fopen(filename, "wb")))
            return -1;

        fwrite(header, sizeof(unsigned char), 54, fp);
        fwrite(image, sizeof(unsigned char), (size_t)(long)xSize * ySize * 3, fp);

        fclose(fp);
        return 0;
    }

private:
    int xSize;
    int ySize;
    unsigned char *image;

    template <class T>
    void swap(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }
};

#endif // _BITMAP_H_ 
