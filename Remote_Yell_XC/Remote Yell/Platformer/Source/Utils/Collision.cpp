#include <Utils/Collision.h>

#include <algorithm>

namespace Platformer
{

namespace Utils
{

const bool Collision::AABBvsAABB(const AABB& one, const AABB& two)
{
	return !(one.Right < two.Left || one.Left > two.Right || one.Bottom < two.Top || one.Top > two.Bottom);
}

const bool Collision::AABBvsLineSegment(const AABB& aabb, const LineSegment& lineSegment)
{
	// TODO:
    return false;
}

} // Utils

} // Platformer
