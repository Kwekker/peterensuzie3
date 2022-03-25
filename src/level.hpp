#ifndef _LEVEL_HPP_
#define _LEVEL_HPP_

#include <stdint.h>
#include <iostream>
#include "gameobject.hpp"

class Level {
    public:
        Level();
        Level(const char *file);
        void readFile(const char *file);
        void draw();

    private:
        uint8_t *data;
        GameObject *elements;
        uint8_t tileWidth;
        uint16_t width;
        uint16_t height;
};

#endif // _LEVEL_HPP_