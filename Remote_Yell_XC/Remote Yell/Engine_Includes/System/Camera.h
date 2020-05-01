#pragma once

#include <Math/Vec2.h>

namespace Internal
{

namespace System
{

class Camera
{
public:

	Camera() = default;
	~Camera() = default;

	const float GetX() const { return myPosition.myX; }
	const float GetY() const { return myPosition.myY; }

	void SetX(const float x) { myPosition.myX = x; }
	void SetY(const float y) { myPosition.myY = y; }

	void SetPosition(const Math::Vec2& pos) { myPosition = pos; }
	const Math::Vec2& GetPosition() const { return myPosition; }

private:

	Math::Vec2 myPosition;
};

} // System

} // Internal
