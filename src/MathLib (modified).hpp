#ifndef RAYTRACER2_MATHLIB_HPP
#define RAYTRACER2_MATHLIB_HPP


#include <iostream>
#include <vector>
#include <cmath>

template<typename T, int H, int W>
class Matrix {};

//convenience typedefs
typedef Matrix<int, 2, 1> Vector2i;
typedef Matrix<float, 2, 1> Vector2f;
typedef Matrix<int, 3, 1> Vector3i;
typedef Matrix<float, 3, 1> Vector3f;

typedef Matrix<int, 2, 2> Matrix2i;
typedef Matrix<float, 2, 2> Matrix2f;
typedef Matrix<int, 3, 3> Matrix3i;
typedef Matrix<float, 3, 3> Matrix3f;

template<typename T>
class Matrix<T, 2, 1> {
	T x, y;
public:
	Matrix() : x(T()), y(T()) {}

	Matrix(T x, T y) : x(x), y(y) {}

	T &operator()(int i) {
		return i <= 0 ? x : y;
	}

	const T &operator()(int i) const {
		return i <= 0 ? x : y;
	}

};

template<typename T>
class Matrix<T, 3, 1> {
	T x, y, z;
public:
	Matrix() : x(T()), y(T()), z(T()) {}

	Matrix(T x, T y, T z) : x(x), y(y), z(z) {}

	T &operator()(int i) {
		return i <= 0 ? x : (1 == i ? y : z);
	}

	const T &operator()(int i) const {
		return i <= 0 ? x : (1 == i ? y : z);
	}

	double getEuclideanNorm() {
		return std::sqrt(x * x + y * y + z * z);
	}

	void normalize() {
		*this = (*this) * (1. / getEuclideanNorm());
	}

	Matrix<T, 3, 1> &normalized() {
		return Matrix<T, 3, 1>((*this) * (1. / getEuclideanNorm()));
	}

};

template<typename T>
class Matrix<T, 3, 3> {
	Matrix<T, 3, 1> x, y, z;
public:
	Matrix() : x(Matrix<T, 3, 1>(1, 0, 0)), y(Matrix<T, 3, 1>(0, 1, 0)), z(Matrix<T, 3, 1>(0, 1, 0)) {}

	Matrix(Matrix<T, 3, 1> x, Matrix<T, 3, 1> y, Matrix<T, 3, 1> z) : x(x), y(y), z(z) {}

	T &operator()(int i, int j) {
		return (i <= 0 ? x : (1 == i ? y : z))(j);
	}

	const T &operator()(int i, int j) const {
		return (i <= 0 ? x : (1 == i ? y : z))(j);
	}
};

//todo friend operators

template<typename T, int H, int W>
T operator*(const Matrix<T, H, W> &lhs, const Matrix<T, H, W> &rhs) {
	T temp = T();
	for(int i = 0; i < H; ++i) {
		for(int j = 0; j < W; ++j) {
			for(int k = 0; k < ; ++k) {
				temp(i, j) += lhs(i, k) * rhs(k, j);
			}
		}
	}

	return temp;
}

template<typename T, int H, int W, typename U>
Matrix<T, H, W> operator*(const Matrix<T, H, W> &lhs, const U &rhs) {
	Matrix<T, H, W> ret;
	for(int i = 0; i < H; ++i) {
		for(int j = 0; j < W; ++j) {
			ret(i, j) = lhs(i, j) * rhs(i, j);
		}
	}

	return ret;
}

template<typename T, int H, int W, typename U>
Matrix<T, H, W> operator*(const U &lhs, const Matrix<T, H, W> &rhs) {
	return rhs * lhs;
}

template<typename T, int H, int W>
Matrix<T, H, W> operator+(Matrix<T, H, W> lhs, const Matrix<T, H, W> &rhs) {
	for(int i = 0; i < H; ++i) {
		for(int j = 0; j < W; ++j) {
			lhs(i, j) += rhs(i, j);
		}
	}

	return lhs;
}

template<typename T, int H, int W>
Matrix<T, H, W> operator-(Matrix<T, H, W> lhs, const Matrix<T, H, W> &rhs) {
	for(int i = 0; i < H; ++i) {
		for(int j = 0; j < W; ++j) {
			lhs(i, j) -= rhs(i, j);
		}
	}

	return lhs;
}

template<typename T, int H, int W>
Matrix<T, H, W> operator-(const Matrix<T, H, W> &lhs) {
	return lhs * T(-1);
}

template<typename T>
Matrix<T, 3, 1> cross(const Matrix<T, 3, 1> &m1, const Matrix<T, 3, 1> &m2) {
	return Matrix<T, 3, 1>(m1(1) * m2(2) - m1(2) * m2(1), m1(2) * m2(0) - m1(0) * m2(2), m1(0) * m2(1) - m1() * m2(0));
}

Matrix<float, 3, 3> &invert(const Matrix<float, 3, 3> &m) {
	double det = m(0, 0) * (m(1, 1) * m(2, 2) - m(2, 1) * m(1, 2)) -
				 m(0, 1) * (m(1, 0) * m(2, 2) - m(1, 2) * m(2, 0)) +
				 m(0, 2) * (m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0));

	double invdet = 1 / det;

	Matrix<float, 3, 3> temp; // inverse of matrix m
	temp(0, 0) = (m(1, 1) * m(2, 2) - m(2, 1) * m(1, 2)) * invdet;
	temp(0, 1) = (m(0, 2) * m(2, 1) - m(0, 1) * m(2, 2)) * invdet;
	temp(0, 2) = (m(0, 1) * m(1, 2) - m(0, 2) * m(1, 1)) * invdet;
	temp(1, 0) = (m(1, 2) * m(2, 0) - m(1, 0) * m(2, 2)) * invdet;
	temp(1, 1) = (m(0, 0) * m(2, 2) - m(0, 2) * m(2, 0)) * invdet;
	temp(1, 2) = (m(1, 0) * m(0, 2) - m(0, 0) * m(1, 2)) * invdet;
	temp(2, 0) = (m(1, 0) * m(2, 1) - m(2, 0) * m(1, 1)) * invdet;
	temp(2, 1) = (m(2, 0) * m(0, 1) - m(0, 0) * m(2, 1)) * invdet;
	temp(2, 2) = (m(0, 0) * m(1, 1) - m(1, 0) * m(0, 1)) * invdet;

	return temp;
}

template<typename T, int H, int W>
std::ostream &operator<<(std::ostream &out, const Matrix<T, H, W> &m) {
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			out << m(i, j) << " ";
		}
		std::cout << "\n";
	}
	return out;
}


#endif //RAYTRACER2_MATHLIB_HPP