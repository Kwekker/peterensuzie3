#include "box.hpp"

// #define DEBUG_COLLISION

Box::Box(Vector pos, Vector size) {
    init(pos << 4);
    this->size = size;
}

void Box::draw() {
    pos += v; 

    SDL_Rect rect = {pos.getX(), pos.getY(), size.x.raw, size.y.raw};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void Box::collision(Level &level) {
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
