//
// Created by kristof on 2019.05.21..
//

#include "Material.hpp"

Material::Material() : color(), reflectance(1, 0, 0), exponent() {}

Material::Material(Vector3f col, Vector3f ref, float exp) : color(col), reflectance(ref), exponent(exp) {}

void Material::setColor(Vector3f col) {
	color = col;
}

Vector3f Material::getColor(float u, float v) const {
	return color;
}

Vector3f Material::getReflectance() const {
	return reflectance;
}

float Material::getExponent() const {
	return exponent;
}
