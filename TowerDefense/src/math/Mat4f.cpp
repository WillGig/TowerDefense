#include "pch.h"

#define PI 3.14159265

Mat4f::Mat4f()
{
	for (int i = 0; i < 16; i++)
		elements[i] = 0;
}

Mat4f::~Mat4f()
{}

Mat4f Mat4f::Identity()
{
	Mat4f result;
	result.elements[0 + 0 * 4] = 1.0f;
	result.elements[1 + 1 * 4] = 1.0f;
	result.elements[2 + 2 * 4] = 1.0f;
	result.elements[3 + 3 * 4] = 1.0f;

	return result;
}

Mat4f Mat4f::Orthographic(float left, float right, float bottom, float top, float near, float far)
{
	Mat4f result = Identity();

	result.elements[0 + 0 * 4] = 2.0f / (right - left);
	result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
	result.elements[2 + 2 * 4] = 2.0f / (near - far);

	result.elements[0 + 3 * 4] = (right + left) / (left - right);
	result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
	result.elements[2 + 3 * 4] = (far + near) / (far - near);

	return result;
}

Mat4f Mat4f::Multiply(const Mat4f& matrix1, const Mat4f& matrix2)
{
	Mat4f result;
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			float sum = 0.0f;
			for (int e = 0; e < 4; e++) {
				sum += matrix1.elements[x + e * 4] * matrix2.elements[e + y * 4];
			}
			result.elements[x + y * 4] = sum;
		}
	}

	return result;
}

Mat4f Mat4f::operator*(const Mat4f& other) const
{
	return Multiply(*this, other);
}

Mat4f Mat4f::Translate(const Vec3& vector)
{
	Mat4f result = Identity();
	result.elements[0 + 3 * 4] = vector.x;
	result.elements[1 + 3 * 4] = vector.y;
	result.elements[2 + 3 * 4] = vector.z;
	return result;
}

//Angle in degrees
Mat4f Mat4f::Rotate(float angle)
{
	Mat4f result = Identity();

	float r = (float)(angle*PI/180);
	float cosine = cos(r);
	float sine = sin(r);

	result.elements[0 + 0 * 4] = cosine;
	result.elements[1 + 0 * 4] = sine;
	result.elements[0 + 1 * 4] = -sine;
	result.elements[1 + 1 * 4] = cosine;
	return result;
}