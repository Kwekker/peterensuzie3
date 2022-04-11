#include "box.hpp"

// #define DEBUG_COLLISION

#define MOVEMENT_STRENGTH 512
#define MOVEMENT_MAX 128
#define FRICTION_FACTOR 0.8

Box::Box(Vector pos, Vector size, Level &level) {
    init(pos << 4);
    this->size = size;
    this->level = &level;
    this->mass.raw = size.x * size.y / MASS_QUOTIENT;
    if(this->mass.raw == 0) {
        this->mass.raw = 1;
        std::cout << "Warning: Box with mass 0" << std::endl;
    }
}
void Box::move(Box* box) {
    Vector displacement = (box->getCenter() - getCenter()).normalize(MOVEMENT_STRENGTH);
    Vector movement = (box->v - v).getComponent(displacement);

    // std::cout << movement << " * " << displacement.toString() << std::endl;
    if(movement.length() < MOVEMENT_MAX || (movement.x & 0x8000) != (displacement.x & 0x8000)) {
        force(-displacement);
        box->force(displacement);
    }
}

Vector Box::getCenter() {
    return pos + Vector(size.x / 2, size.y / 2);
}

void Box::draw(uint8_t frame) {
    if(frame == 0xff || frame == 0) collision();

    if(frame == 0xff || frame == 0) pos += v; 
    else pos += v / SLOWNESS;

    SDL_Rect rect = {pos.getX(), pos.getY(), size.x.raw, size.y.raw};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void Box::collision() {
    //Gravity
    if(!standing) v.y.raw += GRAV;
    
    const Vector nextPos = pos + v;
    const int16_t w = level->getTileWidth();
    int16_t iFrom = (nextPos.x.whole - 1) / level->getTileWidth();
    int16_t iTo = (nextPos.x.whole + size.x + 1) / level->getTileWidth();
    int16_t jFrom = nextPos.y.whole / level->getTileWidth();
    int16_t jTo = (nextPos.y.whole + size.y + 1) / level->getTileWidth();

    if(iFrom < 0) iFrom = 0;
    if(iTo >= level->getWidth()) iTo = level->getWidth() - 1;
    if(jFrom < 0) jFrom = 0;
    if(jTo >= level->getHeight()) jTo = level->getHeight() - 1;

#ifdef DEBUG_COLLISION
    SDL_Rect rect = {nextPos.x.raw, nextPos.y.raw, size.x, size.y};
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 100);
    SDL_RenderFillRect(renderer, &rect);
#endif

    standing = 0;
    for(int16_t i = iFrom; i <= iTo; i++) {
        for(int16_t j = jTo; j >= jFrom; j--) {
            #ifdef DEBUG_COLLISION
            SDL_Rect tileRect = {i * w, j * w, w, w};
            #endif

            if(!level->isPassable(i, j)) {
                #ifdef DEBUG_COLLISION
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 100);
                SDL_RenderFillRect(renderer, &tileRect);
                #endif

                //Top collision
                if(j == jFrom && nextPos.x.whole + 1 < (i + 1) * w && nextPos.x.whole - 1 + size.x > i * w) {
                    pos.setY(j * w + w);
                    v.y.raw = 0;
                    standing |= STANDING_TOP_bm;
                }
                //Bottom collision
                else if(j == jTo && nextPos.x.whole + 1 < (i + 1) * w && nextPos.x.whole - 1 + size.x > i * w) {
                    pos.setY(j * w - size.y);
                    v.y.raw = 0;
                    standing |= STANDING_BOTTOM_bm;
                }
                //Left collision
                if(i == iFrom && j < jTo && j > jFrom) {
                    pos.setX(i * w + w);
                    v.x.raw = 0;
                    standing |= STANDING_LEFT_bm;
                }
                //Right collision
                else if(i == iTo && j < jTo && j > jFrom && v.x.raw > 0) {
                    pos.setX(i * w - size.x);
                    v.x.raw = 0;
                    standing |= STANDING_RIGHT_bm;
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
    if(size.x != 51) std::cout << std::hex << (int)standing << std::endl << std::flush;
    //Friction
    if(v.x.raw != 0 && (standing & STANDING_HORI_gm)) v.x.raw *= FRICTION_FACTOR;
    if(v.y.raw != 0 && (standing & STANDING_VERT_gm)) v.y.raw *= FRICTION_FACTOR;
}
