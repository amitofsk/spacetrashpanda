#include "space_object.h"

Space_Object::Space_Object()
{
    velocity = 5;
    mass = 10;
    direction = 10;
    x = 100;
    y = 100;
}

int Space_Object::getVelocity() {
    return velocity;
}
int Space_Object::getSize() {
    return size;
}
int Space_Object::getDirection() {
    return direction;
}
int Space_Object::getMass() {
    return mass;
}
int Space_Object::getX() {
    return x;
}
int Space_Object::getY() {
    return y;
}
bool Space_Object::getUse() {
    return use;
}
bool Space_Object::getSatellite() {
    return satellite;
}

void Space_Object::setX(int X) {
    x =X;
}
void Space_Object::setY(int Y) {
    y=Y;
}
void Space_Object::setVelocity(int vel) {
    velocity = vel;
}
void Space_Object::setDir(int dir) {
    direction = dir;
}
void Space_Object::setSize(int si) {
    size = si;
}
void Space_Object::setSatellite(bool sat) {
    satellite = sat;
}
void Space_Object::setUse(bool u) {
    use = u;
}
