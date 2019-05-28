//
// Created by kristof on 2019.05.21..
//

#include "Sphere.hpp"


Sphere::Sphere(Vector3f c, const float &r, Material *m) : Object(c, m), radius(r) {}

bool Sphere::intersect(const Vector3f &origin, const Vector3f &direction, float &t) const {
	Vector3f L = position - origin;
	float tca = L * direction;
	float d2 = L * L - tca * tca;
	if (d2 > radius * radius) return false;
	float thc = sqrtf(radius * radius - d2);
	t = tca - thc;
	float t1 = tca + thc;
	if (t < 0) t = t1;
	return t >= 0;
}

Vector3f Sphere::getNormal(const Vector3f &intersect) const {
	return (intersect - position).normalize();
}
