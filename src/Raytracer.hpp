//
// Created by kristof on 2019.05.21..
//

#ifndef RAYTRACER2_RAYTRACER_HPP
#define RAYTRACER2_RAYTRACER_HPP

#include <fstream>
#include <vector>
#include <chrono>

#include "MathLib.hpp"
#include "Camera.hpp"
#include "Scene.hpp"

class Raytracer {
	const Camera &camera;
	const Scene &scene;
	bool simplified;
	unsigned iteration;
	unsigned long totalTime;

	Vector3f castRay(const Vector3f &origin, const Vector3f &direction, int depth = 0);
	bool intersect(const Vector3f &orig, const Vector3f &dir, Vector3f &hit, Vector3f &N, Material &material);
	Vector3f reflect(const Vector3f &I, const Vector3f &N);
public:
	Raytracer(const Camera &c, const Scene &s, bool b);

	void render();

	unsigned long getRenderTime() const;
	unsigned getIterations() const;
	float getAvgTime() const;
};


#endif //RAYTRACER2_RAYTRACER_HPP
