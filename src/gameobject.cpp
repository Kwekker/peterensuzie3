#include "gameobject.hpp"
#include "vector.hpp"

GameObject::GameObject(Vector pos, Vector size) {
    this->pos = pos;
    this->size = size;
    this->mass.raw = size.x * size.y / MASS_QUOTIENT;
    if(this->mass.raw == 0) {
        this->mass.raw = 1;
        std::cout << "Warning: Box with mass 0" << std::endl;
    }
}

void GameObject::force(Vector f) {
    v += f / mass;
}

void GameObject::draw(uint8_t frame) {
    SDL_RenderDrawPoint(renderer, pos.getX(), pos.getY());
}

Vector GameObject::getPos() {
    return pos;
}

void GameObject::setPos(Vector pos) {
    this->pos = pos;
}

Vector GameObject::getV() {
    return v;
}

void GameObject::setV(Vector v) {
    this->v = v;
}

Vector GameObject::getSize() {
    return size;
}
