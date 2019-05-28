#ifndef RAYTRACER1_GEOMETRY_HPP
#define RAYTRACER1_GEOMETRY_HPP


#include <cmath>
#include <vector>
#include <cassert>
#include <iostream>

template<size_t DIM, typename T>
struct vec {
	vec() { for (size_t i = DIM; i--; data_[i] = T()); }

	T &operator[](const size_t i) {
		assert(i < DIM);
		return data_[i];
	}

	const T &operator[](const size_t i) const {
		assert(i < DIM);
		return data_[i];
	}

private:
	T data_[DIM];
};

typedef vec<2, float> Vector2f;
typedef vec<3, float> Vector3f;
typedef vec<2, int> Vector2i;
typedef vec<3, int> Vector3i;
typedef vec<4, float> Vector4f;

template<typename T>
struct vec<2, T> {
	vec() : x(T()), y(T()) {}

	vec(T X, T Y) : x(X), y(Y) {}

	template<class U>
	vec<2, T>(const vec<2, U> &v);

	T &operator[](const size_t i) {
		assert(i < 2);
		return i <= 0 ? x : y;
	}

	const T &operator[](const size_t i) const {
		assert(i < 2);
		return i <= 0 ? x : y;
	}

	T x, y;
};

template<typename T>
struct vec<3, T> {
	vec() : x(T()), y(T()), z(T()) {}

	vec(T X, T Y, T Z) : x(X), y(Y), z(Z) {}

	T &operator[](const size_t i) {
		assert(i < 3);
		return i <= 0 ? x : (1 == i ? y : z);
	}

	const T &operator[](const size_t i) const {
		assert(i < 3);
		return i <= 0 ? x : (1 == i ? y : z);
	}

	float norm() { return std::sqrt(x * x + y * y + z * z); }

	vec<3, T> &normalize(T l = 1) {
		*this = (*this) * (l / norm());
		return *this;
	}

	T x, y, z;
};

template<typename T>
struct vec<4, T> {
	vec() : x(T()), y(T()), z(T()), w(T()) {}

	vec(T X, T Y, T Z, T W) : x(X), y(Y), z(Z), w(W) {}

	T &operator[](const size_t i) {
		assert(i < 4);
		return i <= 0 ? x : (1 == i ? y : (2 == i ? z : w));
	}

	const T &operator[](const size_t i) const {
		assert(i < 4);
		return i <= 0 ? x : (1 == i ? y : (2 == i ? z : w));
	}

	T x, y, z, w;
};

template<size_t DIM, typename T>
T operator*(const vec<DIM, T> &lhs, const vec<DIM, T> &rhs) {
	T ret = T();
	for (size_t i = DIM; i--; ret += lhs[i] * rhs[i]);
	return ret;
}

template<size_t DIM, typename T>
vec<DIM, T> operator+(vec<DIM, T> lhs, const vec<DIM, T> &rhs) {
	for (size_t i = DIM; i--; lhs[i] += rhs[i]);
	return lhs;
}

template<size_t DIM, typename T>
vec<DIM, T> operator-(vec<DIM, T> lhs, const vec<DIM, T> &rhs) {
	for (size_t i = DIM; i--; lhs[i] -= rhs[i]);
	return lhs;
}

template<size_t DIM, typename T, typename U>
vec<DIM, T> operator*(const vec<DIM, T> &lhs, const U &rhs) {
	vec<DIM, T> ret;
	for (size_t i = DIM; i--; ret[i] = lhs[i] * rhs);
	return ret;
}

template<size_t DIM, typename T>
vec<DIM, T> operator-(const vec<DIM, T> &lhs) {
	return lhs * T(-1);
}

template<typename T>
vec<3, T> cross(vec<3, T> v1, vec<3, T> v2) {
	return vec<3, T>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

template<size_t DIM, typename T>
std::ostream &operator<<(std::ostream &out, const vec<DIM, T> &v) {
	for (unsigned int i = 0; i < DIM; i++) {
		out << v[i] << " ";
	}
	return out;
}




template<size_t DIM, typename T>
struct mat {
	mat() {}

	T &operator[](const size_t i) {
		assert(i < DIM);
		return data[i];
	}

	const T &operator[](const size_t i) const {
		assert(i < DIM);
		return data[i];
	}

private:
	vec<DIM, T> data[DIM];
};

template<typename T>
struct mat<3, T> {
	mat() : x(vec<3, T>(1, 0, 0)), y(vec<3, T>(0, 1, 0)), z(vec<3, T>(0, 1, 0)) {}

	mat(vec<3, T> X, vec<3, T> Y, vec<3, T> Z) : x(X), y(Y), z(Z) {}

	vec<3, T> &operator[](const size_t i) {
		assert(i < 3);
		return i <= 0 ? x : (1 == i ? y : z);
	}

	const vec<3, T> &operator[](const size_t i) const {
		assert(i < 3);
		return i <= 0 ? x : (1 == i ? y : z);
	}

	Vector3f mul(const Vector3f& v) const {
		return {
				x[0] * v[0] + x[1] * v[1] + x[2] * v[2],
				y[0] * v[0] + y[1] * v[1] + y[2] * v[2],
				z[0] * v[0] + z[1] * v[1] + z[2] * v[2]
		};
	}

	float operator()(int i, int j) const {
		Vector3f temp = i <= 0 ? x : (1 == i ? y : z);
		return temp[j];
	}

	mat<3, float> inverse(const mat<3, float> &m) const {
		double det = m(0, 0) * (m(1, 1) * m(2, 2) - m(2, 1) * m(1, 2)) -
					 m(0, 1) * (m(1, 0) * m(2, 2) - m(1, 2) * m(2, 0)) +
					 m(0, 2) * (m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0));

		double invdet = 1 / det;

		mat<3, float> minv; // inverse of matrix m
		minv.x[0] = (m(1, 1) * m(2, 2) - m(2, 1) * m(1, 2)) * invdet;
		minv.x[1] = (m(0, 2) * m(2, 1) - m(0, 1) * m(2, 2)) * invdet;
		minv.x[2] = (m(0, 1) * m(1, 2) - m(0, 2) * m(1, 1)) * invdet;
		minv.y[0] = (m(1, 2) * m(2, 0) - m(1, 0) * m(2, 2)) * invdet;
		minv.y[1] = (m(0, 0) * m(2, 2) - m(0, 2) * m(2, 0)) * invdet;
		minv.y[2] = (m(1, 0) * m(0, 2) - m(0, 0) * m(1, 2)) * invdet;
		minv.z[0] = (m(1, 0) * m(2, 1) - m(2, 0) * m(1, 1)) * invdet;
		minv.z[1] = (m(2, 0) * m(0, 1) - m(0, 0) * m(2, 1)) * invdet;
		minv.z[2] = (m(0, 0) * m(1, 1) - m(1, 0) * m(0, 1)) * invdet;

		return minv;
	}

	vec<3, T> x, y, z;
};

typedef mat<3, float> Matrix3f;


#endif //RAYTRACER1_GEOMETRY_HPP