#ifndef _BOX_HPP_
#define _BOX_HPP_

#define DUCK_SPEED 6    << FP
#define JUMP_SPEED 15   << FP

#include "gameobject.hpp"
#include "level.hpp"

class Level;

class Box : public GameObject {
    public:
        Box(Vector pos, Vector size);
        void collision(Level &level);
        void draw();

        Vector getSize() const { return size; }

    protected:
        Vector size;
        uint8_t standing;
};

#endif // _BOX_HPP_