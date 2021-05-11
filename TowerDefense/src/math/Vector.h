#pragma once

struct Vec2
{
	float x, y;
	Vec2()
		:x(0), y(0)
	{}

	Vec2(float x, float y)
		:x(x), y(y)
	{}

	Vec2 operator+(const Vec2& other) const
	{
		return Vec2(x + other.x, y + other.y);
	}

	Vec2 operator-(const Vec2& other) const
	{
		return Vec2(x - other.x, y - other.y);
	}

	Vec2 operator*(const float other) const
	{
		return Vec2(x * other, y * other);
	}
};

struct Vec3
{
	float x, y, z;

	Vec3()
		:x(0), y(0), z(0)
	{}

	Vec3(float x, float y, float z)
		:x(x), y(y), z(z)
	{}

	Vec3 operator+(const Vec3& other) const
	{
		return Vec3(x + other.x, y + other.y, z + other.z);
	}
};

struct Vec4
{
	float w, x, y, z;

	Vec4()
		:w(0), x(0), y(0), z(0)
	{}

	Vec4(float w, float x, float y, float z)
		:w(w), x(x), y(y), z(z)
	{}
};

struct Vec4i
{
	int w, x, y, z;

	Vec4i()
		:w(0), x(0), y(0), z(0)
	{}

	Vec4i(int w, int x, int y, int z)
		:w(w), x(x), y(y), z(z)
	{}
};