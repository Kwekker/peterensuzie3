#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include <stdint.h>
#include <iostream>

#define FP 4
union FPNum {
    int16_t raw;
    struct {
        uint16_t fraction : FP;
        int16_t whole : (16 - FP);
    };

    operator int() { return this->raw; };
    operator FPNum() { return *this; };
};


class Vector {
    public:
        Vector();
        Vector(int16_t x, int16_t y);
        Vector(FPNum x, FPNum y);

        FPNum x;
        FPNum y;

        int16_t getX()    { return x.whole; };
        int16_t getY()    { return y.whole; };
        void setX(int16_t x) { this->x.whole = x; this->x.fraction = 0; };
        void setY(int16_t y) { this->y.whole = y; this->y.fraction = 0; };

        void set(int16_t x, int16_t y);

        Vector normalize(uint8_t newLength);
        Vector operator+(Vector add);
        Vector operator-(Vector add);
        Vector operator*(int mult);
        Vector operator/(int quot);
        Vector operator+=(Vector add);
        Vector operator-=(Vector add);
        Vector operator*=(int mult);
        Vector operator<<(int shift);
        Vector operator>>(int shift);
        
        static Vector v(int16_t x, int16_t y);

        char* toString();

    private:
};

#endif // _VECTOR_HPP_