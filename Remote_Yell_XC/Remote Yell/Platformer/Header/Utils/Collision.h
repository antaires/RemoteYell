#pragma once

#include <EngineInterface.h>

namespace Platformer
{

namespace Utils
{

struct Collision
{
	struct AABB
	{
		Engine::Vec2 Position = { 0.0f, 0.0f };
		Engine::Vec2 Center = { 0.0f, 0.0f };

		int Width = 0;
		int Height = 0;

		float Left = 0.0f;
		float Right = 0.0f;
		float Top = 0.0f;
		float Bottom = 0.0f;
	};

	struct LineSegment
	{
		Engine::Vec2 Start = { 0.0f, 0.0f };
		Engine::Vec2 End = { 0.0f, 0.0f };
	};

	static const bool AABBvsAABB(const AABB& one, const AABB& two);
	static const bool AABBvsLineSegment(const AABB& aabb, const LineSegment& lineSegment);
};

}

}
