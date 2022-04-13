#ifndef _DUCK_HPP_
#define _DUCK_HPP_

#include <stdint.h>
#include <iostream>
#include "vector.hpp"
#include "box.hpp"

class Duck : public Box {
    public:
        Duck(Vector pos, Vector size, Level* level);
        void handleKey(const uint8_t* state, uint8_t frame);
        
    private:
       
};

#endif // _DUCK_HPP_