#ifndef _GAMEOBJECT_HPP_
#define _GAMEOBJECT_HPP_

#include <stdint.h>
#include <SDL2/SDL.h>
#include "vector.hpp"


class GameObject {
    public:

        GameObject();
        GameObject(SDL_Window* window, Vector<> pos, Vector<> size);
        void init(SDL_Window* window, Vector<> pos, Vector<> size);
        void force(Vector<> f);
        void draw();

        Vector<> getPos();
        void setPos(Vector<> pos);
        Vector<> getV();
        void setV(Vector<> v);

    private:
        SDL_Renderer* renderer;
        SDL_Window* window;
        Vector<> pos;
        Vector<> size;
        Vector<> v;
        
};

#endif // _GAMEOBJECT_HPP_
