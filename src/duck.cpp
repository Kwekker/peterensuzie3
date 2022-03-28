#include "duck.hpp"

#define DEBUG_COLLISION

Duck::Duck(Vector<> pos, Vector<> size) {
    init(pos);
    this->size = size;
}

void Duck::handleKey(const uint8_t* state) {
    if(state[SDL_SCANCODE_LEFT] && v.x > -DUCK_SPEED) v.x -= 1;
    else if(state[SDL_SCANCODE_RIGHT] && v.x < DUCK_SPEED) v.x += 1;
    else if(v.x != 0) {
        if(v.x > 0) v.x --;
        else v.x ++;
    }
    if(v.y == 0 && state[SDL_SCANCODE_UP]) {
        v.y -= JUMP_SPEED;
    }
    if(state[SDL_SCANCODE_SPACE]) {
        v += Vector<>(300, 50) - pos;
    }
}

void Duck::draw() {
    pos += v; 

    SDL_Rect rect = {pos.x, pos.y, size.x, size.y};
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void Duck::collision(Level &level) {
    //Gravity
    v.y += 1;

    const Vector<> nextPos = pos + v;
    const int16_t w = level.getTileWidth();
    int16_t iFrom = (nextPos.x - 1) / level.getTileWidth();
    int16_t iTo = (nextPos.x + size.x + 1) / level.getTileWidth();
    int16_t jFrom = nextPos.y / level.getTileWidth();
    int16_t jTo = (nextPos.y + size.y + 1) / level.getTileWidth();

#ifdef DEBUG_COLLISION
    SDL_Rect rect = {nextPos.x, nextPos.y, size.x, size.y};
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 100);
    SDL_RenderFillRect(renderer, &rect);
#endif

    if(iFrom < 0) iFrom = 0;
    if(iTo >= level.getWidth()) iTo = level.getWidth() - 1;
    if(jFrom < 0) jFrom = 0;
    if(jTo >= level.getHeight()) jTo = level.getHeight() - 1;

    //TODO: Only check the sides
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
                if(j == jFrom && nextPos.x + 1 < (i + 1) * w && nextPos.x - 1 + size.x > i * w) {
                    pos.y = j * w + w;
                    v.y = 0;
                }
                //Bottom collision
                else if(j == j && nextPos.x + 1 < (i + 1) * w && nextPos.x - 1 + size.x > i * w) {
                    pos.y = j * w - size.y;
                    v.y = 0;
                    std::cout << "Bottom collision" << std::endl;
                }
                //Left collision
                if(i == iFrom && j < jTo && j > jFrom) {
                    pos.x = i * w + w;
                    v.x = 0;
                }
                //Right collision
                else if(i == iTo && j < jTo && j > jFrom) {
                    pos.x = i * w - size.x;
                    v.x = 0;
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
