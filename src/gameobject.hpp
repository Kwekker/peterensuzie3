#ifndef _GAMEOBJECT_HPP_
#define _GAMEOBJECT_HPP_

#include <stdint.h>
#include <SDL2/SDL.h>
#include "vector.hpp"
#include "globals.hpp"

#define GRAV 1 << FP
#define SLOWNESS 16
#define MASS_QUOTIENT 100


class GameObject {
    public:

        GameObject(Vector pos, Vector size);
        void force(Vector f);
        virtual void draw(uint8_t frame);
        virtual void mouse(uint8_t button, int16_t x, int16_t y) {};

        Vector getPos();
        void setPos(Vector pos);
        Vector getV();
        void setV(Vector v);
        Vector getSize();

    protected:
        Vector pos;
        Vector v;
        FPNum mass = {0};
        Vector size;
        
};

#endif // _GAMEOBJECT_HPP_
