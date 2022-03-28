#ifndef _DUCK_HPP_
#define _DUCK_HPP_

#define DUCK_SPEED 6
#define JUMP_SPEED 15

#include "gameobject.hpp"
#include "level.hpp"

class Level;

class Duck : public GameObject {
    public:
        Duck(Vector<> pos, Vector<> size);
        void handleKey(const uint8_t* state);
        void collision(Level &level);
        void draw();

        Vector<> getSize() const { return size; }

    private:
        Vector<> size;
};

#endif // _DUCK_HPP_