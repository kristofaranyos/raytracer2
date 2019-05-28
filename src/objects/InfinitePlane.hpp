//
// Created by kristof on 2019.05.22..
//

#ifndef RAYTRACER2_PLANE_HPP
#define RAYTRACER2_PLANE_HPP


#include "../MathLib.hpp"
#include "../materials/Material.hpp"

#include "Object.hpp"

class InfinitePlane : public Object {
protected:
	Vector3f normal;
public:
	InfinitePlane(Vector3f p, const Vector3f &n, Material *m);
	~InfinitePlane() override = default;

	bool intersect(const Vector3f &origin, const Vector3f &direction, float &t) const override;
	Vector3f getNormal(const Vector3f &intersect) const override;
};


#endif //RAYTRACER2_PLANE_HPP
