#include "box.hpp"

#define DEBUG_COLLISION

#define MOVEMENT_STRENGTH 530
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

    SDL_Rect rect = {pos.getX(), pos.getY(), size.x, size.y};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void Box::collision() {
    //Gravity
    v.y.raw += GRAV;
    
    Vector nextPos = pos + v + Vector(0, 2 * (standing & STANDING_BOTTOM_bm));
    const int16_t w = level->getTileWidth();
    int16_t iFrom = (nextPos.x.whole) / level->getTileWidth();
    int16_t iTo = (nextPos.x.whole + size.x - 1) / level->getTileWidth() ;
    int16_t jFrom = nextPos.y.whole / level->getTileWidth();
    int16_t jTo = (nextPos.y.whole + size.y - 1) / level->getTileWidth();

    if(iFrom < 0) iFrom = 0;
    if(iTo >= level->getWidth()) iTo = level->getWidth() - 1;
    if(jFrom < 0) jFrom = 0;
    if(jTo >= level->getHeight()) jTo = level->getHeight() - 1;

#ifdef DEBUG_COLLISION
    SDL_Rect rect = {nextPos.x.whole, nextPos.y.whole, size.x, size.y};
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 100);
    SDL_RenderFillRect(renderer, &rect);
#endif

    standing = 0;

    for(int16_t j = jFrom; j <= jTo; j++) {
        uint8_t isTopBottom = (j == jFrom || j == jTo);
        for(int16_t i = iFrom + isTopBottom; i <= iTo - isTopBottom; i += 1 + !isTopBottom * (iTo - iFrom - 1)) {

#ifdef DEBUG_COLLISION
            SDL_Rect rect = {i * w, j * w, w, w};
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 100);
            SDL_RenderDrawRect(renderer, &rect);
#endif

            if(!level->isPassable(i, j)) {

                //Bottom collision
                if(j == jTo) collide(STANDING_BOTTOM_bm, j * w - size.y);

                //Right collision
                if(i == iTo) collide(STANDING_RIGHT_bm, i * w - size.x);
                
                //Top collision
                if(j == jFrom) collide(STANDING_TOP_bm, j * w + w);

                //Left collision
                if(i == iFrom) collide(STANDING_LEFT_bm, i * w + w);
            }
        }
    }

    nextPos = pos;

    #ifdef DEBUG_COLLISION
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    #endif

    //Top right collision
    if(!level->isPassable(iTo, jFrom) && !(standing & STANDING_TOP_bm) && !(standing & STANDING_RIGHT_bm)) {
        Vector check(nextPos.getX() + size.x  -  iTo * w, nextPos.getY()  -  (jFrom * w + w));
        if(check.x < abs(check.y)) collide(STANDING_RIGHT_bm, iTo * w - size.x);
        else collide(STANDING_TOP_bm, jFrom * w + w);
    
        #ifdef DEBUG_COLLISION
        SDL_Rect rect = {iTo * w, jFrom * w, w, w};
        SDL_RenderDrawRect(renderer, &rect);
        #endif
    }
    //Top left collision
    if(!level->isPassable(iFrom, jFrom) && !(standing & STANDING_LEFT_bm) && !(standing & STANDING_TOP_bm)) {
        Vector check(nextPos.getX()  -  (iFrom * w + w), nextPos.getY()  -  (jFrom * w + w));
        if(check.x < check.y) collide(STANDING_TOP_bm, jFrom * w + w);
        else collide(STANDING_LEFT_bm, iFrom * w + w);

        #ifdef DEBUG_COLLISION
        SDL_Rect rect = {iFrom * w, jFrom * w, w, w};
        SDL_RenderDrawRect(renderer, &rect);
        #endif
    }
    //Bottom right collision
    if(!level->isPassable(iTo, jTo) && !(standing & STANDING_BOTTOM_bm) && !(standing & STANDING_RIGHT_bm)) {
        Vector check(nextPos.getX() + size.x  -  iTo * w, nextPos.getY() + size.y  -  jTo * w);
        if(check.x < check.y) collide(STANDING_RIGHT_bm, iTo * w - size.x);
        else collide(STANDING_BOTTOM_bm, jTo * w - size.y);

        #ifdef DEBUG_COLLISION
        SDL_Rect rect = {iTo * w, jTo * w, w, w};
        SDL_RenderDrawRect(renderer, &rect);
        #endif
    }
    //Bottom left collision
    if(!level->isPassable(iFrom, jTo) && !(standing & STANDING_LEFT_bm)) {
        Vector check(nextPos.getX()  -  (iFrom * w + w), nextPos.getY() + size.y  -  jTo * w);
        if(abs(check.x) < check.y) collide(STANDING_LEFT_bm, iFrom * w + w);
        else collide(STANDING_BOTTOM_bm, jTo * w - size.y);

        #ifdef DEBUG_COLLISION
        SDL_Rect rect = {iFrom * w, jTo * w, w, w};
        SDL_RenderDrawRect(renderer, &rect);
        #endif
    }

    if(size.x != 51) std::cout << std::hex << (int)standing << std::endl << std::flush;
    //Friction
    if(v.x.raw != 0 && (standing & STANDING_HORI_gm)) v.x.raw *= FRICTION_FACTOR;
    if(v.y.raw != 0 && (standing & STANDING_VERT_gm)) v.y.raw *= FRICTION_FACTOR;
}

void Box::collide(uint8_t axis, int16_t pos) {
    if(axis & STANDING_VERT_gm) {
        v.x.raw = 0;
        this->pos.setX(pos);
    }
    else {
        v.y.raw = 0;
        this->pos.setY(pos);
    }
    standing |= axis;
}
