#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

template <typename Coord>
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

#endif // _VECTOR_HPP_