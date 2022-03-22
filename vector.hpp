#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include <stdint.h>
#include <iostream>

template <typename Coord = int16_t>
class Vector {
    public:
        Vector();
        Vector(Coord x, Coord y);

        Coord x;
        Coord y;

        void set(Coord x, Coord y);

        Vector operator+(Vector add);
        Vector operator-(Vector add);
        Vector operator*(int mult);
        Vector operator+=(Vector add);
        Vector operator-=(Vector add);
        Vector operator*=(int mult);

    private:
};

#include "vector.tpp"

#endif