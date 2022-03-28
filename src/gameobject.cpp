#include "gameobject.hpp"
#include "vector.hpp"

GameObject::GameObject() {
}

GameObject::GameObject(Vector<int16_t> pos) {
    this->pos = pos;
}

void GameObject::init(Vector<int16_t> pos) {
    this->pos = pos;
}

void GameObject::force(Vector<> f) {
    v += f;
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
