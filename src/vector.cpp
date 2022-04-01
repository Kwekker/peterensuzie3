#include "vector.hpp"
#include <cmath>

Vector::Vector() {
    x.raw = 0;
    y.raw = 0;
}

Vector::Vector(int16_t x, int16_t y) {
    this->x.raw = x;
    this->y.raw = y;
}
Vector::Vector(FPNum x, FPNum y) {
    this->x.raw = x.raw;
    this->y.raw = y.raw;
}

void Vector::set(int16_t x, int16_t y) {
    this->x.whole = x;
    this->y.whole = y;
}

Vector Vector::normalize(uint8_t newLength) {
    uint16_t length = sqrt((x.raw * x.raw) + (y.raw * y.raw));
    if(!length) length = 1;
    return Vector(newLength * x.raw / length, newLength * y.raw / length);
}

Vector Vector::operator+(Vector add) {
    return Vector(x + add.x, y + add.y);
}

Vector Vector::operator-(Vector sub) {
    return Vector(x - sub.x, y - sub.y);
}

Vector Vector::operator/(int quot) {
    return Vector(x / quot, y / quot);
}

Vector Vector::operator*(int mult) {
    return Vector(x.whole * mult, y.whole * mult);
}

Vector Vector::operator+=(Vector add) {
    return Vector(x.raw += add.x, y.raw += add.y);
}

Vector Vector::operator-=(Vector sub) {
    return Vector(x.raw -= sub.x, y.raw -= sub.y);
}

Vector Vector::operator*=(int mult) {
    return Vector(x.raw *= mult, y.raw *= mult);
}

Vector Vector::operator<<(int shift) {
    return Vector(x << shift, y << shift);
}

Vector Vector::operator>>(int shift) {
    return Vector(x >> shift, y >> shift);
}

Vector Vector::v(int16_t x, int16_t y) {
    Vector ret;
    ret.set(x, y);
    return ret;
}

char* Vector::toString() {
    static char ret[15];
    sprintf(ret, "[%d, %d]", x.raw, y.raw);
    return ret;
}