#include "gameobject.hpp"
#include "vector.hpp"

GameObject::GameObject() {
}

GameObject::GameObject(Vector<int16_t> pos, Vector<int16_t> size) {
    this->pos = pos;
    this->size = size;
}

void GameObject::init(Vector<int16_t> pos, Vector<int16_t> size) {
    this->pos = pos;
    this->size = size;
}

void GameObject::force(Vector<> f) {
    v += f;
}

void GameObject::draw() {
    pos += v;
    SDL_Rect rect = {pos.x, pos.y, size.x, size.y};
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