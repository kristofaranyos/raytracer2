//
// Created by kristof on 2019.05.21..
//

#include "PointLight.hpp"

Vector3f Light::getPosition() const {
	return position;
}

float Light::getIntensity() const {
	return intensity;
}

Light::Light(Vector3f p, float i) : position(p), intensity(i) {}

void Light::setPosition(Vector3f pos) {
	position = pos;
}
