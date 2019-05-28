//
// Created by kristof on 2019.05.21..
//

#ifndef RAYTRACER2_CAMERA_HPP
#define RAYTRACER2_CAMERA_HPP


#include "MathLib.hpp"

class Camera {
	Vector3f eye;
	Vector3f center;
	Vector3f up;
	Vector2i resolution;
	//todo fov
public:
	Camera(Vector3f eye, Vector3f center, Vector3f up, Vector2i resolution);

	void translateEye(Vector3f offset);
	void setEyePos(Vector3f pos);
	Vector3f getEye() const;
	void setCenterPos(Vector3f pos);
	Vector3f getCenter() const;
	Vector3f getUp() const;
	Vector2i getResolution() const;
	Matrix3f getViewMatrix() const;

};


#endif //RAYTRACER2_CAMERA_HPP
