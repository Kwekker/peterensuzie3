#include "duck.hpp"

Duck::Duck(Vector<> pos, Vector<> size) {
    init(pos, size);
}

void Duck::handleKey(const uint8_t* state) {
    // if(((state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_LEFT]) && abs(v.x) != DUCK_SPEED) || v.x != 0) {
    //     int8_t sign = 1;
    //     if(state[SDL_SCANCODE_LEFT] || ) sign = -1;
    //     v.x += sign;
    // }
    if(state[SDL_SCANCODE_RIGHT]) v.x = DUCK_SPEED;
    else if(state[SDL_SCANCODE_LEFT]) v.x = -DUCK_SPEED;
    else v.x = 0;
}
