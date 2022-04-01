#ifndef _DUCK_HPP_
#define _DUCK_HPP_

#include <stdint.h>
#include <iostream>
#include "gameobject.hpp"
#include "level.hpp"
#include "vector.hpp"
#include "box.hpp"

#define DUCK_SPEED 6    << FP
#define JUMP_SPEED 15   << FP

class Duck : public Box {
    public:
        Duck(Vector pos, Vector size);
        void handleKey(const uint8_t* state, uint8_t frame);
        
    private:
       
};

#endif // _DUCK_HPP_