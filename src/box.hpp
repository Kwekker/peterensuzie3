#ifndef _BOX_HPP_
#define _BOX_HPP_

#include "gameobject.hpp"
#include "level.hpp"

#define STANDING_RIGHT_bm   0b0001
#define STANDING_TOP_bm     0b0010
#define STANDING_LEFT_bm    0b0100
#define STANDING_BOTTOM_bm  0b1000

//This refers to the ground the object is touching
#define STANDING_HORI_gm    0b1010
#define STANDING_VERT_gm    0b0101

// force = steepness / (speed + steepness / max)

class Level;

class Box : public GameObject {
    public:
        Box(Vector pos, Vector size, Level &level);
        void collision(uint8_t slow);
        void draw(uint8_t frame);
        void move(Box* box, uint8_t pull);
        void mouse(uint8_t button, int16_t x, int16_t y);
        Vector getCenter();

        Vector getSize() { return size; }
    protected:
        void collide(uint8_t axis, int16_t coord);
        Level* level;
        uint8_t standing = 0;
        uint8_t moving = 0;
};

#endif // _BOX_HPP_
