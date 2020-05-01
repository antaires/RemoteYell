#include <Gameplay/Components/PlayerMovementComponent.h>

#include <Gameplay/Components/InputComponent.h>

namespace Platformer
{

namespace Gameplay
{

void PlayerMovementComponent::EvaluateMovementIntent(Engine::Vec2& outIntent, MoveStateChange& outState)
{
    auto* inputC = myParent->GetComponent<InputComponent>();

    float moveSpeed = Constants::k_moveSpeed;
    if (inputC->KeyDown("left shift"))
    {
        moveSpeed *= Constants::k_sprintFactor;
    }

    if (inputC->KeyDown("a"))
    {
        outIntent.myX = -moveSpeed;
    }
    if (inputC->KeyDown("d"))
    {
        outIntent.myX = moveSpeed;
    }

    // Handle state changes.
    outState = MoveStateChange_None;

    if (inputC->KeyDown("space"))
    {
        outState = MoveStateChange_Jump;
    }
}

} // Gameplay

} // Platformer

