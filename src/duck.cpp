#include "duck.hpp"

#define DEBUG_COLLISION

Duck::Duck(Vector pos, Vector size) {
    init(pos << 4);
    this->size = size;
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
        Vector w = (point - pos);
        std::cout << "space " << w.toString() << " normed: " << w.normalize(32).toString() << std::endl << std::flush;
        v += w.normalize(32);
    }
}

void Duck::draw() {
    pos += v; 

    SDL_Rect rect = {pos.getX(), pos.getY(), size.x.raw, size.y.raw};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void Duck::collision(Level &level) {
    //Gravity
    if(!standing) v.y.raw += GRAV;

    const Vector nextPos = pos + v;
    const int16_t w = level.getTileWidth();
    int16_t iFrom = (nextPos.x.whole - 1) / level.getTileWidth();
    int16_t iTo = (nextPos.x.whole + size.x + 1) / level.getTileWidth();
    int16_t jFrom = nextPos.y.whole / level.getTileWidth();
    int16_t jTo = (nextPos.y.whole + size.y + 1) / level.getTileWidth();

#ifdef DEBUG_COLLISION
    SDL_Rect rect = {nextPos.x.raw, nextPos.y.raw, size.x, size.y};
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 100);
    SDL_RenderFillRect(renderer, &rect);
#endif

    if(iFrom < 0) iFrom = 0;
    if(iTo >= level.getWidth()) iTo = level.getWidth() - 1;
    if(jFrom < 0) jFrom = 0;
    if(jTo >= level.getHeight()) jTo = level.getHeight() - 1;

    standing = 0;
    for(int16_t i = iFrom; i <= iTo; i++) {
        for(int16_t j = jTo; j >= jFrom; j--) {
            #ifdef DEBUG_COLLISION
            SDL_Rect tileRect = {i * w, j * w, w, w};
            #endif

            if(!level.isPassable(i, j)) {
                #ifdef DEBUG_COLLISION
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 100);
                SDL_RenderFillRect(renderer, &tileRect);
                #endif

                //Top collision
                if(j == jFrom && nextPos.x.whole + 1 < (i + 1) * w && nextPos.x.whole - 1 + size.x > i * w) {
                    pos.setY(j * w + w);
                    v.y.raw = 0;
                }
                //Bottom collision
                else if(j == j && nextPos.x.whole + 1 < (i + 1) * w && nextPos.x.whole - 1 + size.x > i * w) {
                    pos.setY(j * w - size.y);
                    v.y.raw = 0;
                    standing = 1;
                }
                //Left collision
                if(i == iFrom && j < jTo && j > jFrom) {
                    pos.setX(i * w + w);
                    v.x.raw = 0;
                }
                //Right collision
                else if(i == iTo && j < jTo && j > jFrom && v.x.raw > 0) {
                    pos.setX(i * w - size.x);
                    v.x.raw = 0;
                }
            }
            #ifdef DEBUG_COLLISION
            else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 100);
                SDL_RenderFillRect(renderer, &tileRect);
            }
            #endif
        }
    }
}
