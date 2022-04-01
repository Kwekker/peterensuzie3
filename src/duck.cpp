#include "duck.hpp"

Duck::Duck(Vector pos, Vector size) : Box(pos, size) {

}

void Duck::handleKey(const uint8_t* state, uint8_t frame) {
    if(standing) {
        //Controls
        if(state[SDL_SCANCODE_LEFT] && v.x.raw > -DUCK_SPEED) v.x.whole -= 1;
        else if(state[SDL_SCANCODE_RIGHT] && v.x < DUCK_SPEED) v.x.whole += 1;
        //Friction
        else if(v.x != 0) {
            if(v.x.whole == 0) v.x.raw = 0;
            else if(v.x.raw > 0) v.x.whole -= 1;
            else v.x.whole += 1;
        }
    }

    //Jumping
    if(standing && v.y.raw == 0 && (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W])) {
        v.y.raw -= JUMP_SPEED;
        standing = 0;
    }

    //Pulling and Pushing
    if(state[SDL_SCANCODE_SPACE] && (frame == 0 || frame == 0xff)) {
        Vector point;
        point.set(300, 50);
        point -= Vector::v(size.x / 2, size.y / 2);
        v += (point - pos).normalize(32);
    }
}

