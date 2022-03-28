#include "ball.hpp"

Ball::Ball(Vector<> pos, uint8_t size) {
    this->pos = pos;
    this->size = size;
}

void Ball::collision(Level &level) {
    
}

void Ball::draw() {
    pos += v; 

    SDL_Rect rect = {pos.x, pos.y, size, size};
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}