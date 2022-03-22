#ifndef _GAMEOBJECT_HPP_
#define _GAMEOBJECT_HPP_

#include <stdint.h>
#include <SDL2/SDL.h>
#include "vector.hpp"
#include "globals.hpp"


class GameObject {
    public:

        GameObject();
        GameObject(Vector<> pos, Vector<> size);
        void init(Vector<> pos, Vector<> size);
        void force(Vector<> f);
        void draw();

        Vector<> getPos();
        void setPos(Vector<> pos);
        Vector<> getV();
        void setV(Vector<> v);

    protected:
        Vector<> pos;
        Vector<> size;
        Vector<> v;
        
};

#endif // _GAMEOBJECT_HPP_
