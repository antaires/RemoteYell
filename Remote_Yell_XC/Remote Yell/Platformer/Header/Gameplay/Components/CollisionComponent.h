#pragma once

#include <EngineInterface.h>

#include <Utils/Collision.h>

namespace Platformer
{

namespace Gameplay
{

class CollisionComponent : public Engine::Component
{
private:
    using AABB = Utils::Collision::AABB;

public:

    CollisionComponent(const int width, const int height, const int xOffset = 0, const int yOffset = 0);
    ~CollisionComponent() override = default;

    void Update(const double dt) override;

    void CheckCollision(const Engine::Vec2& proposal, Engine::Vec2& minima) const;

    const AABB& GetBounds() const { return myBounds; }

private:

    void UpdateAABB(const Engine::Vec2& position, AABB& out) const;

    AABB myBounds = {};
    Engine::Vec2 myOffset = {};
};

} // Gameplay

} // Platformer

