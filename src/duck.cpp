#include "duck.hpp"

#define DUCK_SPEED 32
#define JUMP_SPEED 240

Duck::Duck(Vector pos, Vector size, Level* level) : Box(pos, size, level) {

}

void Duck::handleKey(const uint8_t* state, uint8_t frame) {

    //Jumping
    if((standing & STANDING_BOTTOM_bm) && v.y.raw == 0 && (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W])) {
        v.y.raw -= JUMP_SPEED;
        standing = 0;
    }

    //Walking
    if(standing & STANDING_HORI_gm) {
        if(state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]) v.x.raw -= DUCK_SPEED;
        else if(state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D]) v.x.raw += DUCK_SPEED;
    }
    else if(standing & STANDING_VERT_gm) {
        if(state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]) v.y.raw -= DUCK_SPEED;
        else if(state[SDL_SCANCODE_DOWN]  || state[SDL_SCANCODE_S]) v.y.raw += DUCK_SPEED / 2;
    }
}

