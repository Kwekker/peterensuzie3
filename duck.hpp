#ifndef _DUCK_HPP_
#define _DUCK_HPP_

#define DUCK_SPEED 6

#include "gameobject.hpp"

class Duck : public GameObject {
    public:
        Duck(Vector<> pos, Vector<> size);
        void handleKey(const uint8_t* state);

    private:

};

#endif // _DUCK_HPP_