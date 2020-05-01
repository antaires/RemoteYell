#pragma once


#include <Gameplay/Component.h>
#include <Math/Vec2.h>

#include <Tools/CollisionPrimitives.h>

namespace Internal
{

namespace Gameplay
{

class TileCollisionComponent : public Component
{
private:

	using AABB = Tools::CollisionPrimitives::AABB;

public:

	TileCollisionComponent() = default;
	~TileCollisionComponent() override = default;

	void Update(const double dt) override {}

	void CheckCollision(const Math::Vec2& proposal, Math::Vec2& minima) const;

private:
};

} // Gameplay

} // Internal
