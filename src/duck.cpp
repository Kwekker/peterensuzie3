#include "duck.hpp"

#define DUCK_SPEED 28
#define JUMP_SPEED 240

Duck::Duck(Vector pos, Vector size, Level &level) : Box(pos, size, level) {

}

void Duck::handleKey(const uint8_t* state, uint8_t frame) {

    //Jumping
    if(standing && v.y.raw == 0 && (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W])) {
        v.y.raw -= JUMP_SPEED;
        standing = 0;
    }

    //Walking
    else if(standing) {
        if(state[SDL_SCANCODE_LEFT]) v.x.raw -= DUCK_SPEED;
        else if(state[SDL_SCANCODE_RIGHT]) v.x.raw += DUCK_SPEED;
    }
}

