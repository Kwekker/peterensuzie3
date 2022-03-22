#ifndef _GAMEOBJECT_HPP_
#define _GAMEOBJECT_HPP_

#include <stdint.h>
#include <SDL2/SDL.h>
#include "vector.hpp"


class GameObject {
    public:

        GameObject();
        GameObject(SDL_Window* window, uint16_t x, uint16_t y, uint16_t sizeX, uint16_t sizeY);
        void init(SDL_Window* window, uint16_t x, uint16_t y, uint16_t sizeX, uint16_t sizeY);
        void draw();
        
        Vector<int16_t> getPos();
        void setPos(Vector<int16_t> pos);
        Vector<int16_t> getV();
        void setV(Vector<int16_t> v);

    private:
        SDL_Renderer* renderer;
        SDL_Window* window;
        Vector<int16_t> pos;
        Vector<int16_t> v;
        uint16_t x;
        uint16_t y;
        uint16_t sizeX;
        uint16_t sizeY;
};

#endif // !_GAMEOBJECT_HPP_