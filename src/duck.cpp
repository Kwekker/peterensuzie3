#include "duck.hpp"

Duck::Duck(Vector pos, Vector size) : Box(pos, size) {

}

void Duck::handleKey(const uint8_t* state) {
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
    if(standing && v.y.raw == 0 && state[SDL_SCANCODE_UP]) {
        v.y.raw -= JUMP_SPEED;
        standing = 0;
    }
    if(state[SDL_SCANCODE_SPACE]) {
        Vector point;
        point.set(300, 50);
        point -= Vector::v(size.x / 2, size.y / 2);
        v += (point - pos).normalize(32);
    }
}

