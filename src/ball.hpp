#ifndef _BALL_HPP_
#define _BALL_HPP_

#include "gameobject.hpp"
#include "vector.hpp"
#include "level.hpp"

class Ball : public GameObject {
    public:
        Ball(Vector<> pos, uint8_t size);
        void collision(Level &level);
        void draw();
        uint8_t getSize() const { return size; };

    private:
        uint8_t size;
};

#endif // _BALL_HPP_