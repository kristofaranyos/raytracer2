//
// Created by kristof on 2019.05.21..
//

#include "Raytracer.hpp"
#include <limits>

Raytracer::Raytracer(const Camera &c, const Scene &s, bool b, int m)
		: camera(c), scene(s), simplified(b), maxDepth(m), iteration(0), totalTime(0) {}

Vector3f Raytracer::reflect(const Vector3f &I, const Vector3f &N) {
	return I - N * 2.f * (I * N);
}

bool Raytracer::intersect(const Vector3f &orig, const Vector3f &dir, Vector3f &hit, Vector3f &N, Material &material) {
	float spheres_dist = std::numeric_limits<float>::max();
	for (size_t i = 0; i < scene.getObjectCount(); i++) {
		float dist_i;
		if (scene.getObject(i)->intersect(orig, dir, dist_i) && dist_i < spheres_dist) {
			spheres_dist = dist_i;
			hit = orig + dir * dist_i;
			N = scene.getObject(i)->getNormal(hit);
			material = *scene.getObject(i)->getMaterial();
		}
	}
	return spheres_dist < 1000;
}

Vector3f Raytracer::castRay(const Vector3f &origin, const Vector3f &direction, int depth) {
	Vector3f point, N;
	Material material;

	if (depth > (simplified ? 1 : 4) || !intersect(origin, direction, point, N, material)) {
		return scene.getBackgroundColor(); // background color
	}

	Vector3f reflect_dir = reflect(direction, N).normalize();
	Vector3f reflect_orig = reflect_dir * N < 0 ? point - N * 1e-3 : point + N * 1e-3;
	Vector3f reflect_color = castRay(reflect_orig, reflect_dir, depth + 1);

	float diffuse_light_intensity = 0, specular_light_intensity = 0;
	for (size_t i = 0; i < scene.getLightCount(); i++) {
		Vector3f light_dir = (scene.getLight(i)->getPosition() - point).normalize();

		//shadow
		if (!simplified) {
			float light_distance = (scene.getLight(i)->getPosition() - point).norm();

			Vector3f shadow_orig = light_dir * N < 0 ? point - N * 1e-3 : point + N * 1e-3;
			Vector3f shadow_pt, shadow_N;
			Material tmpmaterial;
			if (intersect(shadow_orig, light_dir, shadow_pt, shadow_N, tmpmaterial) &&
				(shadow_pt - shadow_orig).norm() < light_distance)
				continue;
		}

		diffuse_light_intensity += scene.getLight(i)->getIntensity() * std::max(0.f, light_dir * N);
		specular_light_intensity +=
				powf(std::max(0.f, -reflect(-light_dir, N) * direction), material.getExponent()) *
				scene.getLight(i)->getIntensity();
	}

	return material.getColor(point.x, point.z) * diffuse_light_intensity * material.getReflectance()[0] +
		   Vector3f(1, 1, 1) * specular_light_intensity * material.getReflectance()[1] + reflect_color * material.getReflectance()[2];
}

void Raytracer::render() {
	auto begin = std::chrono::high_resolution_clock::now();

	const int fov = static_cast<const int>(M_PI / 2.); //todo fov

	std::vector<Vector3f> frameBuffer(camera.getResolution().x * camera.getResolution().y);

	
	#pragma omp parallel for
	for (size_t j = 0; j < camera.getResolution().y; j++) {
		for (size_t i = 0; i < camera.getResolution().x; i++) {
			float x = (2 * (i + 0.5) / (float) camera.getResolution().x - 1) * tan(fov / 2.) * camera.getResolution().x / (float)camera.getResolution().y;
			float y = -(2 * (j + 0.5) / (float) camera.getResolution().y - 1) * tan(fov / 2.);
			Vector3f temp = Vector3f(x, y, -1).normalize();

			Matrix3f viewMatrix = camera.getViewMatrix();
			Vector3f dir = viewMatrix.mul(temp);

			frameBuffer[i + j * camera.getResolution().x] = castRay(camera.getEye(), dir);
		}
	}


	std::ofstream ofs;
	ofs.open("../output/test" + std::to_string(iteration) + ".ppm");
	ofs << "P6\n" << camera.getResolution().x << " " << camera.getResolution().y << "\n255\n";
	for (size_t i = 0; i < camera.getResolution().x * camera.getResolution().y; ++i) {
		for (size_t j = 0; j < 3; j++) {
			ofs << (char) (255 * std::max(0.f, std::min(1.f, frameBuffer[i][j])));
		}
	}
	ofs.close();


	auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::high_resolution_clock::now() - begin).count();
	++iteration;
	totalTime += diff;
	std::cout << iteration << ". done in: " << diff << "ms, avg: " << getAvgTime() << "ms" << std::endl;
}

unsigned long Raytracer::getRenderTime() const {
	return totalTime;
}

unsigned Raytracer::getIterations() const {
	return iteration;
}

float Raytracer::getAvgTime() const {
	return (float) totalTime / iteration;
}