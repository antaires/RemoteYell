#pragma once

#include <Gameplay/Components/MovementComponent.h>

namespace Platformer
{

namespace Gameplay
{

class PlayerMovementComponent : public MovementComponent
{
public:

    PlayerMovementComponent() = default;
    ~PlayerMovementComponent() override = default;

protected:

    void EvaluateMovementIntent(Engine::Vec2& outIntent, MoveStateChange& outState) override;

    struct Constants
    {
        static constexpr float k_moveSpeed = 350.0f;
        static constexpr float k_sprintFactor = 1.5f;
    };
};

} // Gameplay

} // Platformer

