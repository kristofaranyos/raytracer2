//
// Created by kristof on 2019.05.30..
//

#include "Triangle.hpp"

Triangle::Triangle(Vector3f p0, Vector3f p1, Vector3f p2, Material *m) : InfinitePlane(p0, cross(p0 - p1, p0 - p2).normalize(), m), p1(p1), p2(p2) {}

bool Triangle::intersect(const Vector3f &origin, const Vector3f &direction, float &t) const {
	if (!InfinitePlane::intersect(origin, direction, t)) {
		return false;
	}

	Vector3f edge0 = p1 - position;
	Vector3f edge1 = p2 - p1;
	Vector3f edge2 = position - p2;

	Vector3f P = origin + direction * t;

	Vector3f C0 = P - position;
	Vector3f C1 = P - p1;
	Vector3f C2 = P - p2;

	return normal * cross(edge0, C0) > 0 && normal * cross(edge1, C1) > 0 && normal * cross(edge2, C2) > 0;

}