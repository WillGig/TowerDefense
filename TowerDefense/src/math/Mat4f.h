#pragma once
#include "Vector.h"

struct Mat4f
{
	float elements[16];

	Mat4f();
	~Mat4f();

	static Mat4f Identity();

	static Mat4f Orthographic(float left, float right, float bottom, float top, float near, float far);

	static Mat4f Multiply(const Mat4f& matrix1, const Mat4f& matrix2);

	Mat4f operator*(const Mat4f& other) const;

	//Returns translation matrix with specified vector
	static Mat4f Translate(const Vec3& vector);

	//Returns rotation matrix at specified angle in degrees
	static Mat4f Rotate(float angle);
};