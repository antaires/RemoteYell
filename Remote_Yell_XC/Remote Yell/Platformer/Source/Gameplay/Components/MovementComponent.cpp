#include <Gameplay/Components/MovementComponent.h>

#include <Gameplay/Components/FiringComponent.h>
//#include <Gameplay/Components/CollisionComponent.h>
#include <Gameplay/Components/AnimRenderComponent.h>

#include <Utils/Math.h>

#include <algorithm>
#include <float.h>

namespace Platformer
{

namespace Gameplay
{

void MovementComponent::Update(const double dt)
{
    Engine::Vec2 intent = { 0.0f, Constants::k_gravity };

    MoveStateChange moveState = MoveStateChange_None;
    EvaluateMovementIntent(intent, moveState);

    const bool hasJumpInput = (moveState == MoveStateChange_Jump);
    HandleJumping(dt, hasJumpInput, intent);

    ApplyPhysics(dt, intent);
    
    // Restrict movement based on any collisions to find actual amount we should move by.
    Engine::Vec2 minima = { FLT_MAX, FLT_MAX };
    ProcessCollisions(dt, intent, minima);

    // Integrate the movement.
    auto* transformC = myParent->EditComponent<Engine::SystemTransformComponent>();
    auto position = transformC->GetPosition();

    Engine::Vec2 offset = {
        Utils::Math::Sign(intent.myX) * std::min(std::abs(intent.myX), minima.myX),
        Utils::Math::Sign(intent.myY) * std::min(std::abs(intent.myY), minima.myY)
    };

    // Moving down.
    if (intent.myY > 0.0f && !hasJumpInput)
    {
        const bool onFloor = minima.myY < std::abs(intent.myY);
        if (onFloor)
            myOnFloorTime = Engine::GetGameTime();
    }

    position += offset;
    transformC->SetPosition(position);

    // Now animate the character if necessary.
    auto* animC = myParent->SafeEditComponent<AnimRenderComponent>();
    if (animC == nullptr)
        return;

    // We are on the floor if we're intending to move down, but are being stopped.
    const bool onFloor = ((intent.myY > 0.0f) && (minima.myY < std::abs(intent.myY)));

    animC->EvaluateDrawState(offset, onFloor);
}

void MovementComponent::HandleJumping(const double dt, const bool hasJumpInput, Engine::Vec2& outIntent)
{
    double timeSinceFloor = Engine::GetGameTime() - myOnFloorTime;
    const bool canJump = timeSinceFloor < Constants::k_jumpTime;

    if (canJump && hasJumpInput)
    {
        const float jumpPercent = static_cast<float>(timeSinceFloor) / Constants::k_jumpTime;
        float proportion = 1.0f - (std::powf(jumpPercent, Constants::k_jumpFallOffExponent));

        const float speed = proportion * Constants::k_jumpForce;

        outIntent.myY = speed;
    }
}

void MovementComponent::ApplyPhysics(const double dt, Engine::Vec2& outMovement)
{
    myVelocity = (outMovement * Constants::k_acceleration) + (myVelocity * (1 - Constants::k_acceleration));
    outMovement = myVelocity * static_cast<float>(dt);
}

void MovementComponent::ProcessCollisions(const double dt, const Engine::Vec2& desiredMove, Engine::Vec2& outOverlap)
{
    // First we check if we even need to process collision for this entity.
    auto* collisionC = myParent->SafeGetComponent<Engine::SystemTileCollisionComponent>();
    if (collisionC == nullptr)
        return;

    collisionC->CheckCollision(desiredMove, outOverlap);
}

} // Gameplay

} // Platformer

