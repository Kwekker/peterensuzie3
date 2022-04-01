#include "gameobject.hpp"
#include "vector.hpp"

GameObject::GameObject() {
}

GameObject::GameObject(Vector pos) {
    this->pos = pos;
}

void GameObject::init(Vector pos) {
    this->pos = pos;
}

void GameObject::force(Vector f) {
    v += f;
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
