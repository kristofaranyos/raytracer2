//
// Created by kristof on 2019.05.25..
//

#include "BoundedPlane.hpp"

BoundedPlane::BoundedPlane(Vector3f p, Vector3f v1, Vector3f v2, Material *m) : InfinitePlane(p, cross(v1, v2).normalize(), m), u(v1), v(v2) {
	transform = Matrix3f {
			Vector3f(u.x, normal.x, v.x),
			Vector3f(u.y, normal.y, v.y),
			Vector3f(u.z, normal.z, v.z)
	};

	transform = transform.inverse(transform);
}

bool BoundedPlane::intersect(const Vector3f &origin, const Vector3f &direction, float &t) const {
	if (!InfinitePlane::intersect(origin, direction, t)) {
		return false;
	}

	Vector3f local = transform.mul((origin + direction * t) - position);

	return local.x >= 0 && local.x <= 1 && local.z >= 0 && local.z <= 1;
}