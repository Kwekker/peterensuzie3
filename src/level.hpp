#ifndef _LEVEL_HPP_
#define _LEVEL_HPP_

#include <stdint.h>
#include <iostream>
#include "gameobject.hpp"
#include "duck.hpp"

class Duck;

class Level {
    public:
        Level();
        Level(const char *file);
        void readFile(const char *file);
        void draw();
        uint8_t isPassable(uint16_t i, uint16_t j);

        uint8_t getTileWidth() const { return size; }
        uint16_t getWidth() const { return width; }
        uint16_t getHeight() const { return height; }
        uint8_t getData(uint16_t i, uint16_t j);

        uint8_t isColliding(uint8_t i, uint8_t j, Duck* duck);

    private:
        uint8_t *data;
        GameObject *elements;
        uint8_t size;
        uint16_t width;
        uint16_t height;
};

#endif // _LEVEL_HPP_