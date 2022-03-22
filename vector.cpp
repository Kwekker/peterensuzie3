#include "vector.hpp"

template<typename Coord>
Vector<Coord>::Vector() {
    x = 0;
    y = 0;
}

template<typename Coord>
Vector<Coord>::Vector(Coord x, Coord y) {
    this->x = x;
    this->y = y;
}

template<typename Coord>
void Vector<Coord>::set(Coord x, Coord y) {
    this->x = x;
    this->y = y;
}

template<typename Coord>
Vector<Coord> Vector<Coord>::operator+(Vector add) {
    return Vector(x + add.x, y + add.y);
}

template<typename Coord>
Vector<Coord> Vector<Coord>::operator-(Vector sub) {
    return Vector(x - sub.x, y - sub.y);
}

template<typename Coord>
Vector<Coord> Vector<Coord>::operator*(int mult) {
    return Vector(x * mult, y * mult);
}

template<typename Coord>
Vector<Coord> Vector<Coord>::operator+=(Vector add) {
    return Vector(x += add.x, y += add.y);
}

template<typename Coord>
Vector<Coord> Vector<Coord>::operator-=(Vector sub) {
    return Vector(x -= sub.x, y -= sub.y);
}

template<typename Coord>
Vector<Coord> Vector<Coord>::operator*=(int mult) {
    return Vector(x *= mult, y *= mult);
}