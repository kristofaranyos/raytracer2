//
// Created by kristof on 2019.05.30..
//

#ifndef RAYTRACER2_TRIANGLE_HPP
#define RAYTRACER2_TRIANGLE_HPP


#include "../MathLib.hpp"
#include "../materials/Material.hpp"

#include "InfinitePlane.hpp"

class Triangle : public InfinitePlane{
protected:
	Vector3f p1, p2;
	Matrix3f transform;
public:
	Triangle(Vector3f p0, Vector3f p1, Vector3f p2, Material *m);
	~Triangle() override = default;

	bool intersect(const Vector3f &origin, const Vector3f &direction, float &t) const override;
};


#endif //RAYTRACER2_TRIANGLE_HPP