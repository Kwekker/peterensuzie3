#ifndef _GAMEOBJECT_HPP_
#define _GAMEOBJECT_HPP_

#include <stdint.h>
#include <SDL2/SDL.h>
#include "vector.hpp"
#include "globals.hpp"


class GameObject {
    public:

        GameObject();
        GameObject(Vector<> pos);
        void init(Vector<> pos);
        void force(Vector<> f);

        Vector<> getPos();
        void setPos(Vector<> pos);
        Vector<> getV();
        void setV(Vector<> v);

    protected:
        Vector<> pos;
        Vector<> v;
        
};

#endif // _GAMEOBJECT_HPP_
