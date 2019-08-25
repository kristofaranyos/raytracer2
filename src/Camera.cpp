//
// Created by kristof on 2019.05.21..
//

#include "Camera.hpp"

Camera::Camera(Vector3f eye, Vector3f center, Vector3f up, Vector2i resolution)
		: eye(eye), center(center), up(up), resolution(resolution) {

}

void Camera::translateEye(Vector3f offset) {
	eye = eye + offset;
}

void Camera::setEyePos(Vector3f pos) {
	eye = pos;
}

Vector3f Camera::getEye() const {
	return eye;
}

void Camera::setCenterPos(Vector3f pos) {
	center = pos;
}

Vector3f Camera::getCenter() const {
	return center;
}

Vector3f Camera::getUp() const {
	return up;
}

Vector2i Camera::getResolution() const {
	return resolution;
}

Matrix3f Camera::getViewMatrix() const {
	Vector3f tempNorm = Vector3f(up).normalize();
	Vector3f lookAtNorm = (eye - center).normalize();
	Vector3f rightNorm = cross(tempNorm, lookAtNorm).normalize();
	Vector3f upNorm = cross(lookAtNorm, rightNorm).normalize();

	//return transpose of viewmatrix (orthogonal => transpose = inverse)
	return {
		rightNorm,
		upNorm,
		lookAtNorm
	};
}