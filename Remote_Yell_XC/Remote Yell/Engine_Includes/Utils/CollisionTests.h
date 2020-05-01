#pragma once

#include <Tools/CollisionPrimitives.h>
#include <Gameplay/EntityManager.h>
#include <Math/Vec2.h>

namespace Internal
{

namespace Utils
{

struct CollisionTests
{
	using Point = Tools::CollisionPrimitives::Point;
	using AABB = Tools::CollisionPrimitives::AABB;
	using Circle = Tools::CollisionPrimitives::Circle;
	using Ray = Tools::CollisionPrimitives::Ray;

	static const bool PointVsAABB(const Point& point, const AABB& aabb);
	static const bool PointVsCircle(const Point& point, const Circle& circle);

	static const bool AABBVsAABB(const AABB& one, const AABB& two);
	static const bool AABBVsCircle(const AABB& aabb, const Circle& circle);
	static const bool CircleVsCircle(const Circle& one, const Circle& two);

	static const bool AABBVsEntities(const AABB& aabb, const Gameplay::EntityID_List& entites, Gameplay::EntityID_List& hits);
	static const bool CircleVsEntities(const Circle& circle, const Gameplay::EntityID_List& entites, Gameplay::EntityID_List& hits);
	
	static const bool RayVsAABB(const Ray& ray, const float distance, const AABB& aabb, Point* outIntersectionPoint = nullptr);
	static const bool RayVsCirlce(const Ray& ray, const float distance, const Circle& circle, Point* outIntersectionPoint = nullptr);
	static const bool RayVsWorld(const Ray& ray, const float distance, Point* outIntersectionPoint = nullptr);

};

} // Utils

} // Internal
