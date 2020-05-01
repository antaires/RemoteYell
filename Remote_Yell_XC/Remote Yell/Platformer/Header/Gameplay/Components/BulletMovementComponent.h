#pragma once

#include <Gameplay/Components/MovementComponent.h>
#include <Gameplay/EntityType.h>


namespace Platformer
{

namespace Gameplay
{

class BulletMovementComponent : public MovementComponent
{
public:

    BulletMovementComponent() = default;
    ~BulletMovementComponent() override = default;
    
    void SetVelocity(Engine::Vec2& velocity);
    void Update(const double dt) override;
    void SetType(EntityType type);
    EntityType GetEntityType() const;
protected:

    virtual void EvaluateMovementIntent(Engine::Vec2& outIntent, MoveStateChange& outState) override { }

    Engine::Vec2 myVelocity = { 0.0f, 0.0f };
    Engine::Vec2 myAcceleration = { 0.0f, 0.0f };
    EntityType myType;
    
    double myOnFloorTime = 0.0;
    void ApplyPhysics(const double dt, Engine::Vec2& outMovement);
    void ProcessCollisions(const double dt, const Engine::Vec2& desiredMove, Engine::Vec2& outOverlap);
    
    struct Constants
    {
        static constexpr float k_gravity = 1000.0f;
        static constexpr float k_moveSpeed = 1000.0f;
        static constexpr float k_acceleration = 0.08f;
        static constexpr int k_damage = 10;
    };
};

} // Gameplay

} // Platformer

