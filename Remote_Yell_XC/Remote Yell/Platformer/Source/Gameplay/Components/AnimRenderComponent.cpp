#include <Gameplay/Components/AnimRenderComponent.h>
#include <Gameplay/Components/HealthComponent.h>
#include <Gameplay/Components/FiringComponent.h>

#include <cassert>
#include <iostream>

namespace Platformer
{

namespace Gameplay
{

AnimRenderComponent::AnimRenderComponent(Engine::SpriteSheet& spriteSheet, const AnimFrameMap& animMap, Engine::RenderOrder order)
    : Engine::SystemRenderComponent(spriteSheet, order)
    , myDrawStates(animMap)
{
}

void AnimRenderComponent::Render()
{
    auto& anim = myDrawStates.at(myDrawState);
    
    double currentTime = Engine::GetGameTime();
    if (myDrawTimer != 0.0)
    {
        if ((currentTime - myDrawTimer) > Constants::k_animStepSec)
        {
            myAnimIndex++;
            // Wrap back to 0.
            if (myAnimIndex >= anim.Length && isAlive)
                myAnimIndex = 0;
            else if (myAnimIndex >= anim.Length){
                myAnimIndex = anim.Length - 1;
            }
            
            myDrawTimer = 0.0;
        }
    }
    else
        myDrawTimer = currentTime;

    // Calculate the target frame.
    int frame = anim.StartFrame + myAnimIndex;
    
    myDrawIndex = frame;

    Engine::SystemRenderComponent::Render();
}

void AnimRenderComponent::EvaluateDrawState(const Engine::Vec2& moveIntent, bool onFloor)
{
    auto* healthC = myParent->SafeGetComponent<HealthComponent>();
    if (healthC != NULL){
        if (!healthC->GetIsAlive())
        {
            SetDrawState(DrawState_Hurt);
            isAlive = false;
            return;
        }
    }
    
    auto* firingC = myParent->SafeGetComponent<FiringComponent>();
    const bool isFiring = firingC && firingC->GetIsFiring();

    if (!onFloor)
    {
        SetDrawState(isFiring ? DrawState_JumpFiring : DrawState_Jump);
    }
    else if (std::abs(moveIntent.myX) > Constants::k_animSpeedEpsilon)
    {
        DrawState normal = DrawState_Walk_Straight;
        DrawState firing = DrawState_WalkFiring_Straight;

        if (firingC != nullptr)
        {
            if (firingC->GetAimDirection() == Aiming_DiagUp)
            {
                normal = DrawState_Walk_DiagUp;
                firing = DrawState_WalkFiring_DiagUp;

            }
            else if (firingC->GetAimDirection() == Aiming_DiagDown)
            {
                normal = DrawState_Walk_DiagDown;
                firing = DrawState_WalkFiring_DiagDown;
            }
        }

        SetDrawState(isFiring ? firing : normal);
    }
    else
    {
        DrawState firing = DrawState_StandFiring_Straight;

        if (firingC != nullptr)
        {
            if (firingC->GetAimDirection() == Aiming_DiagUp)
            {
                firing = DrawState_StandFiring_DiagUp;
            }
            else if (firingC->GetAimDirection() == Aiming_DiagDown)
            {
                firing = DrawState_StandFiring_DiagDown;
            }
        }

        SetDrawState(isFiring ? firing : DrawState_Stand_Straight);
    }

    myFlipped = (moveIntent.myX < 0.0f);
    
}

void AnimRenderComponent::SetDrawState(DrawState state)
{
    // Don't try to set it to a state that doesn't exist.
    if (myDrawStates.count(state) == 0)
        return;

    // Reset anim index when we change state.
    if (myDrawState != state)
    {
        myAnimIndex = 0;
    }

    myDrawState = state;
}

} // Gameplay

} // Platformer

