#pragma once

#include <math.h> 

namespace Internal
{

namespace Math
{

class Vec2
{
public:

	Vec2() = default;

	Vec2(float anX, float anY)
	{
		myX = anX;
		myY = anY;
	}

	Vec2(int anX, int aY)
	{
		myX = static_cast<float>(anX);
		myY = static_cast<float>(aY);
	}



	bool operator==(const Vec2 &other) const
	{
		return myX == other.myX && myY == other.myY;
	}
	bool operator!=(const Vec2 &other) const
	{
		return !(*this == other);
	}
	
	const Vec2 operator-(const Vec2 &other) const
	{
		Vec2 v(myX - other.myX, myY - other.myY);
		return v;
	}

	const Vec2 operator+(const Vec2 &other) const
	{
		Vec2 v(myX + other.myX, myY + other.myY);
		return v;
	}

	const Vec2 operator*(const Vec2& other) const
	{
		Vec2 v(myX*other.myX, myY*other.myY);
		return v;
	}

	const Vec2 operator/(const Vec2& other) const
	{
		Vec2 v(myX/other.myX, myY/other.myY);
		return v;
	}

	Vec2& operator+=(const Vec2 &other)
	{
		myX = myX + other.myX;
		myY = myY + other.myY;

		return *this;
	}

	Vec2& operator-=(const Vec2 &other)
	{
		myX = myX - other.myX;
		myY = myY - other.myY;

		return *this;
	}

	Vec2& operator*=(const float aFloat)
	{
		myX *= aFloat;
		myY *= aFloat;

		return *this;
	}

	Vec2& operator/=(const float aFloat)
	{
		myX /= aFloat;
		myY /= aFloat;

		return *this;
	}

	const Vec2 operator*(const float aValue) const
	{
		Vec2 v(myX * aValue, myY * aValue);
		return v;
	}

	const Vec2 operator/(const float aValue) const
	{
		Vec2 v(myX / aValue, myY / aValue);
		return v;
	}

	float Length() const
	{
		return sqrtf(myX*myX + myY*myY);
	}

	float SqrLength() const
	{
		return (myX*myX + myY*myY);
	}

	void Normalize()
	{
		float length = Length();

		if (length > 0.0f)
			*this /= length;
	}

	void Clamp(const float min, const float max)
	{
		if (myX < min) myX = min;
		if (myY < min) myY = min;
		if (myX > max) myX = max;
		if (myY > max) myY = max;
	}

	void Clamp(const Math::Vec2& min, const Math::Vec2& max)
	{
		if (myX < min.myX) myX = min.myX;
		if (myY < min.myY) myY = min.myY;
		if (myX > max.myX) myX = max.myX;
		if (myY > max.myY) myY = max.myY;
	}

	float Dot(const Vec2& other) const
	{
		return (myX * other.myX) + (myY * other.myY);
	}

	// Default-initialised to 0.
	float myX = 0.0f;
	float myY = 0.0f;
};

} // Math

} // Internal
