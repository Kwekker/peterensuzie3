#include "duck.hpp"

Duck::Duck(Vector<> pos, Vector<> size) {
    init(pos, size);
}

void Duck::handleKey(const uint8_t* state) {
    if(state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_LEFT]){
        if(abs(v.x) <= DUCK_SPEED) {
            if(state[SDL_SCANCODE_LEFT]) v.x -= 1;
            else v.x += 1;
        }
    }
    else if(v.x != 0) {
        if(v.x > 0) v.x --;
        else v.x ++;
    }
}
