
#pragma once

#include <Gameplay/Components/MovementComponent.h>
#include <Gameplay/MoveStateChange.h>


namespace Platformer
{

namespace Gameplay
{

class EnemyMovementComponent : public MovementComponent
{
public:
    
    EnemyMovementComponent() = default;
    ~EnemyMovementComponent() override = default;
    MoveStateChange GetMoveState() const;
    const Engine::Vec2 GetMoveIntent() const;
    void SetPositionLock(bool lock);
protected:

    void EvaluateMovementIntent(Engine::Vec2& outIntent, MoveStateChange& outState) override;
    Engine::Vec2 GetPlayerPosition();
    void SwitchPatrolDirection();
    Engine::EntityId storedPlayerId = INT_MIN;
    MoveStateChange myMoveState = MoveStateChange_None;
    MoveStateChange prevMoveState = MoveStateChange_None;
    Engine::Vec2 myMoveIntent = {0.0f, 0.0f};
    int patrolDirection = 1;
    int patrolTimer = 0;
    bool positionLocked = false;
    
    struct Constants
    {
        static constexpr float k_moveSpeed = 300.0f;
        static constexpr float k_sprintFactor = 1.5f;
        static constexpr float k_attackDistance = 300.0f;
        static constexpr float k_detectionDistance = 500.f;
        static constexpr float k_patrolClock = 100.0f;
    };
};

} // Gameplay

} // Platformer

