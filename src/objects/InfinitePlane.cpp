//
// Created by kristof on 2019.05.22..
//

#include "InfinitePlane.hpp"

InfinitePlane::InfinitePlane(Vector3f c, const Vector3f &n, Material *m) : Object(c, m), normal(n) {}

bool InfinitePlane::intersect(const Vector3f &origin, const Vector3f &direction, float &t) const {
	t = normal * (position - origin) / (normal * direction);
	return t > 0;
}

Vector3f InfinitePlane::getNormal(const Vector3f &intersect) const {
	return normal;
}
