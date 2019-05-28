//
// Created by kristof on 2019.05.21..
//

#ifndef RAYTRACER2_MATERIAL_HPP
#define RAYTRACER2_MATERIAL_HPP


#include "../MathLib.hpp"

class Material {
protected:
	Vector3f color;
	Vector3f reflectance;
	float exponent;
public:
	Material();
	Material(Vector3f color, Vector3f a, float spec);
	virtual ~Material() = default;

	void setColor(Vector3f col);
	virtual Vector3f getColor(float u, float v) const;

	Vector3f getReflectance() const;

	float getExponent() const;
};


#endif //RAYTRACER2_MATERIAL_HPP