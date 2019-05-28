//
// Created by kristof on 2019.05.21..
//

#ifndef RAYTRACER2_OBJECT_HPP
#define RAYTRACER2_OBJECT_HPP

#include "../MathLib.hpp"
#include "../materials/Material.hpp"

class Object {
protected:
	Vector3f position;
	Material *material;
public:
	Object(Vector3f p, Material *m);
	virtual ~Object() = default;

	virtual bool intersect(const Vector3f &origin, const Vector3f &direction, float &t) const = 0;

	Vector3f getPosition() const;
	void setPosition(Vector3f pos);

	Material *getMaterial() const;

	virtual Vector3f getNormal(const Vector3f &intersect) const = 0;
};


#endif //RAYTRACER2_OBJECT_HPP
