//
// Created by kristof on 2019.05.21..
//

#ifndef RAYTRACER2_LIGHT_HPP
#define RAYTRACER2_LIGHT_HPP


#include "../MathLib.hpp"

class Light {
	Vector3f position;
	float intensity;
public:
	Light(Vector3f p, float i);

	Vector3f getPosition() const;
	void setPosition(Vector3f pos);
	float getIntensity() const;
};


#endif //RAYTRACER2_LIGHT_HPP
