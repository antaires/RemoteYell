#pragma once

#include <Math/Vec2.h>

namespace Internal
{

namespace Tools
{

struct CollisionPrimitives
{
	using Point = Math::Vec2;

	struct AABB
	{
		bool operator==(const AABB &other);
		bool operator!=(const AABB &other);

		AABB& operator=(const AABB &other);

		AABB& operator+=(const Math::Vec2 &offset);
		AABB& operator-=(const Math::Vec2 &offset);

		AABB() {}

		AABB(const Math::Vec2& dimensions)
			: TopLeft(0.0f, 0.0f)
			, BottomRight(dimensions)
		{}


		Math::Vec2 TopLeft = { 0.0f, 0.0f };
		Math::Vec2 BottomRight = { 0.0f, 0.0f };
	};

	struct Circle
	{
		bool operator==(const Circle &other);
		bool operator!=(const Circle &other);

		Circle& operator+=(const Math::Vec2 &offset);
		Circle& operator-=(const Math::Vec2 &offset);


		Math::Vec2 Position = { 0.0f, 0.0f };
		float Radius = 0.0f;
	};

	struct Ray
	{
		bool operator==(const Ray &other);
		bool operator!=(const Ray &other);

		Math::Vec2 Position = { 0.0f, 0.0f };
		Math::Vec2 Direction = { 0.0f, 0.0f };
	};
};

} // Tools

} // Internal
