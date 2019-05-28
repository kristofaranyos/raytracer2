//
// Created by kristof on 2019.05.21..
//

#ifndef RAYTRACER2_SPHERE_HPP
#define RAYTRACER2_SPHERE_HPP


#include "Object.hpp"
#include "../materials/Material.hpp"

class Sphere : public Object {
	float radius;
public:
	Sphere(Vector3f c, const float &r, Material *m);
	~Sphere() override = default;

	bool intersect(const Vector3f &origin, const Vector3f &direction, float &t) const override;
	Vector3f getNormal(const Vector3f &intersect) const override;
};






#endif //RAYTRACER2_SPHERE_HPP