//
// Created by kristof on 2019.05.21..
//

#include "Object.hpp"

Object::Object(Vector3f p, Material *m) : position(p), material(m) {}

Vector3f Object::getPosition() const {
	return position;
}

Material *Object::getMaterial() const {
	return material;
}

void Object::setPosition(Vector3f pos) {
	position = pos;
}
