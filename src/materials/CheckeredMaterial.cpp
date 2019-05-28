//
// Created by kristof on 2019.05.25..
//

#include "CheckeredMaterial.hpp"

CheckeredMaterial::CheckeredMaterial() : Material() {}

CheckeredMaterial::CheckeredMaterial(Vector3f color, Vector3f a, float spec) : Material(color, a, spec) {}

Vector3f CheckeredMaterial::getColor(float u, float v) const {
	return (sin(u * 2 * M_PI / 5) > 0.5) ^ (cos(v * 2 * M_PI / 5) > 0.5) ? color : Vector3f(1, 1, 1);
}
