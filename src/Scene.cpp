//
// Created by kristof on 2019.05.21..
//

#include "Scene.hpp"

Scene::Scene(Vector3f bgc) : backgroundColor(bgc) {}

Scene::~Scene() {
	for (auto element : objects) {
		delete element;
	}

	for (auto element : lights) {
		delete element;
	}
}

Vector3f Scene::getBackgroundColor() const {
	return backgroundColor;
}

Object *Scene::getObject(int index) const {
	return objects[index];
}

void Scene::addObject(Object *o) {
	objects.push_back(o);
}

int Scene::getObjectCount() const {
	return objects.size();
}

Light *Scene::getLight(int index) const {
	return lights[index];
}

void Scene::addLight(Light *l) {
	lights.push_back(l);
}

int Scene::getLightCount() const {
	return lights.size();
}