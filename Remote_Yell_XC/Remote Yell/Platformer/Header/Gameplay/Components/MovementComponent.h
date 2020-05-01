#pragma once

#include <EngineInterface.h>
#include <Gameplay/MoveStateChange.h>

namespace Platformer
{

namespace Gameplay
{

class MovementComponent : public Engine::Component
{
public:

    MovementComponent() = default;
    ~MovementComponent() override = default;
    
    void Update(const double dt) override;

protected:

    virtual void EvaluateMovementIntent(Engine::Vec2& outIntent, MoveStateChange& outState) { }

    Engine::Vec2 myVelocity = { 0.0f, 0.0f };
    Engine::Vec2 myAcceleration = { 0.0f, 0.0f };

    double myOnFloorTime = 0.0;

private:

    void HandleJumping(const double dt, const bool hasJumpInput, Engine::Vec2& outIntent);
    void ApplyPhysics(const double dt, Engine::Vec2& outMovement);
    void ProcessCollisions(const double dt, const Engine::Vec2& desiredMove, Engine::Vec2& outOverlap);

    struct Constants
    {
        static constexpr float k_gravity = 1000.0f;
        
        static constexpr float k_jumpForce = -30000.0f;
        static constexpr float k_jumpTime = 0.225f;
        static constexpr float k_jumpFallOffExponent = 0.1f;
        
        static constexpr float k_acceleration = 0.08f;
    };
};

} // Gameplay

} // Platformer

