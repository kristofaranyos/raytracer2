//
// Created by kristof on 2019.05.25..
//

#ifndef RAYTRACER2_BOUNDEDPLANE_HPP
#define RAYTRACER2_BOUNDEDPLANE_HPP


#include "../MathLib.hpp"
#include "../materials/Material.hpp"

#include "InfinitePlane.hpp"

class BoundedPlane : public InfinitePlane{
protected:
	Vector3f u, v;
	Matrix3f transform;
public:
	BoundedPlane(Vector3f p, Vector3f v1, Vector3f v2, Material *m);
	~BoundedPlane() override = default;

	bool intersect(const Vector3f &origin, const Vector3f &direction, float &t) const override;
};


#endif //RAYTRACER2_BOUNDEDPLANE_HPP
