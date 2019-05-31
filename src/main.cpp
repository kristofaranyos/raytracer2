#include <iostream>

//vector math
#include "MathLib.hpp"

//core stuff
#include "Camera.hpp"
#include "Scene.hpp"
#include "Raytracer.hpp"

//lights
#include "lights/PointLight.hpp"

//materials
#include "materials/Material.hpp"
#include "materials/CheckeredMaterial.hpp"

//objects
#include "objects/Object.hpp"
#include "objects/Sphere.hpp"
#include "objects/InfinitePlane.hpp"
#include "objects/BoundedPlane.hpp"

int main() {
	try {
		//debug options, default = false
		const bool ONE_PIC_MODE = true;
		const bool SIMPLE_LIGHTING = true;

		//output parameters
		const uint32_t FPS = 20;
		const uint32_t LENGTH = 3;
		const uint32_t SCREEN_WIDTH = 1920;
		const uint32_t SCREEN_HEIGHT = 1080;

		Camera camera(Vector3f(0, 10, 0), Vector3f(0, 10, -25), Vector3f(0, 1, 0), Vector2i(SCREEN_WIDTH, SCREEN_HEIGHT));
		Scene scene(Vector3f(0.5, 0.7, 1));

		//spheres
		scene.addObject(new Sphere(Vector3f(-20, 2, -31), 2, new Material(Vector3f(0.2, 0.3, 0.9), Vector3f(0.6, 0.3, 0.2), 50))); //kek
		scene.addObject(new Sphere(Vector3f(-10, 3, -35), 3, new Material(Vector3f(0.9, 1, 0), Vector3f(0.6, 0.3, 0.5), 50))); //sarga
		scene.addObject(new Sphere(Vector3f(-1, 2, -20), 2, new Material(Vector3f(0.1, 0.4, 0.2), Vector3f(0.9, 0.1, 0.1), 10))); //zold
		scene.addObject(new Sphere(Vector3f(1, 3, -33), 3, new Material(Vector3f(0.3, 0.1, 0.1), Vector3f(0.9, 0.1, 0.0), 10))); //piros
		scene.addObject(new Sphere(Vector3f(9, 12, -33), 4, new Material(Vector3f(0.7, 0.2, 0.4), Vector3f(0.5, 1, 0.9), 50))); //rozsaszin

		//rectangles
		float boxSize = 50;

		Material *whiteWall = new Material(Vector3f(0.8, 0.8, 0.8), Vector3f(0.3, 0.1, 0), 40);

		scene.addObject(new BoundedPlane(Vector3f(boxSize / 2, boxSize, 0), Vector3f(-boxSize, 0, 0), Vector3f(0, 0, -boxSize), whiteWall)); //teteje
		scene.addObject(new BoundedPlane(Vector3f(-boxSize / 2, 0, 0), Vector3f(boxSize, 0, 0), Vector3f(0, 0, -boxSize), whiteWall)); //alja

		scene.addObject(new BoundedPlane(Vector3f(-boxSize / 2, 0, 0), Vector3f(0, boxSize, 0), Vector3f(boxSize, 0, 0), whiteWall)); //elol (kamera mogott)
		scene.addObject(new BoundedPlane(Vector3f(-boxSize / 2, 0, -boxSize), Vector3f(boxSize, 0, 0), Vector3f(0, boxSize, 0), whiteWall)); //hatul (kamera elott)

		scene.addObject(new BoundedPlane(Vector3f(-boxSize / 2, 0, 0), Vector3f(0, 0, -boxSize), Vector3f(0, boxSize, 0), new Material(Vector3f(1, 0, 0), Vector3f(0.3, 0.1, 0), 40))); //bal
		scene.addObject(new BoundedPlane(Vector3f(boxSize / 2, 0, 0), Vector3f(0, boxSize, 0), Vector3f(0, 0, -boxSize), new Material(Vector3f(0, 1, 0), Vector3f(0.3, 0.1, 0), 40))); //jobb


		//lights
		scene.addLight(new Light(Vector3f(0, 40, -35), 1.8)); //felso
		//scene.addLight(new Light(Vector3f(30, 20, 30), 1.7));

		Raytracer raytracer(camera, scene, SIMPLE_LIGHTING);

		float dt = 1000.f / FPS;
		int duration = 1000 * LENGTH;
		int iterations = std::ceil(duration / dt);

		std::cout << "images to compute: " << (ONE_PIC_MODE ? 1 : iterations) << std::endl;

		for (int i = 0; i < (ONE_PIC_MODE ? 1 : iterations); ++i) {
			float t = i * dt;
			//update camera and scene
			//scene.getObject(1)->setPosition(Vector3f(-1, 3, -20) + Vector3f(sin(t / 6000.f * 2.f * M_PI) * 20, sin(t / 3000.f * 2.f * M_PI) * 5, cos(t / 6000.f * 2.f * M_PI) * 20));

			//camera.setEyePos(Vector3f(0, 15, -2*iterations));
			//render
			raytracer.render();

		}

		std::cout << "render time: " << raytracer.getRenderTime() / 1000.f << " seconds, avg: "
				  << raytracer.getAvgTime() << " ms, total: " << raytracer.getIterations() << " images" << std::endl;
	} catch (const std::exception &e) {
		std::cout << e.what();
		return 1;
	}

	return 0;
}
