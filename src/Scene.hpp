//
// Created by kristof on 2019.05.21..
//

#ifndef RAYTRACER2_SCENE_HPP
#define RAYTRACER2_SCENE_HPP

#include <vector>

#include "objects/Object.hpp"
#include "lights/PointLight.hpp"

class Scene {
	std::vector<Object *> objects;
	std::vector<Light *> lights;
	Vector3f backgroundColor;

public:
	explicit Scene(Vector3f bgc);
	~Scene();

	Vector3f getBackgroundColor() const;

	Object *getObject(int index) const;
	void addObject(Object *o);
	int getObjectCount() const;

	Light *getLight(int index) const;
	void addLight(Light *l);
	int getLightCount() const;
};


#endif //RAYTRACER2_SCENE_HPP
