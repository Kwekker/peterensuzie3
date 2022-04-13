#ifndef _LEVEL_HPP_
#define _LEVEL_HPP_

#include <stdint.h>
#include <iostream>
#include "duck.hpp"

class Level {
    public:
        Level();
        Level(const char *file);
        void readFile(const char *file);
        void draw();
        void run(uint8_t frame, const uint8_t* state);
        void mouse(uint8_t button, int16_t x, int16_t y);
        uint8_t isPassable(uint16_t i, uint16_t j);

        uint8_t getTileWidth() const { return size; }
        uint16_t getWidth() const { return width; }
        uint16_t getHeight() const { return height; }
        uint8_t getData(uint16_t i, uint16_t j);
        Duck *getPlayer();

    private:
        uint8_t *data;
        uint8_t size; //size of each tile
        uint16_t width;
        uint16_t height;
    
        GameObject **elements;
        Duck *player;
        uint8_t elementsAmount;
};

#endif // _LEVEL_HPP_