#include "gameobject.hpp"

GameObject::GameObject() {
    
}

GameObject::GameObject(SDL_Window* window, uint16_t x, uint16_t y, uint16_t sizeX, uint16_t sizeY) {
    this->window = window;
    this->renderer = SDL_GetRenderer(window);
    this->x = x;
    this->y = y;
    this->sizeX = x;
    this->sizeY = y;
}

void GameObject::init(SDL_Window* window, uint16_t x, uint16_t y, uint16_t sizeX, uint16_t sizeY) {
    this->window = window;
    this->renderer = SDL_GetRenderer(window);
    this->x = x;
    this->y = y;
    this->sizeX = x;
    this->sizeY = y;
}

void GameObject::draw() {
    int width, height;
    SDL_GetWindowSize(window, &width, &height);
    if(y + 5 < height) y += 5;

    SDL_Rect rect = {x, y, sizeX, sizeY};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

}

Vector<int16_t> GameObject::getPos() {
    return pos;
}

void GameObject::setPos(Vector<int16_t> pos) {
    this->pos = pos;
}

Vector<int16_t> GameObject::getV() {
    return v;
}

void GameObject::setV(Vector<int16_t> v) {
    this->v = v;
}