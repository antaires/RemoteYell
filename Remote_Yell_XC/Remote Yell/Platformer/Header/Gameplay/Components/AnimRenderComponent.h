#pragma once

#include <EngineInterface.h>

#include <map>
#include <vector>

namespace Platformer
{

namespace Gameplay
{

// Note: editing this enum will necessitate altering the structure of the JSON animation files.
enum DrawState
{
    // Aiming straight forwards.
    DrawState_Stand_Straight = 0,
    DrawState_Walk_Straight,
    DrawState_StandFiring_Straight,
    DrawState_WalkFiring_Straight,
    // Diagonally upwards.
    DrawState_Walk_DiagUp,
    DrawState_StandFiring_DiagUp,
    DrawState_WalkFiring_DiagUp,
    // Diagonally downwards.
    DrawState_Walk_DiagDown,
    DrawState_StandFiring_DiagDown,
    DrawState_WalkFiring_DiagDown,
    // Jumping.
    DrawState_Jump,
    DrawState_JumpFiring,
    // Death.
    DrawState_Hurt,
};

class AnimRenderComponent : public Engine::SystemRenderComponent
{
public:

    struct SpriteAnim
    {
        unsigned int StartFrame;
        unsigned int Length;
    };
    using AnimFrameMap = std::map<DrawState, SpriteAnim>;

    AnimRenderComponent(Engine::SpriteSheet& spriteSheet, const AnimFrameMap& animMap, Engine::RenderOrder order);
    ~AnimRenderComponent() override = default;

    void Update(const double dt) override {}
    void Render() override;
    void SetDrawState(DrawState state);
    void EvaluateDrawState(const Engine::Vec2& moveIntent, bool onFloor);

private:

    AnimFrameMap myDrawStates = {};
    DrawState myDrawState = DrawState_Stand_Straight;

    double myDrawTimer = 0.0;
    unsigned int myAnimIndex = 0;
    bool isAlive = true;
    struct Constants
    {
        static constexpr float k_animStepSec = 0.15f;
        static constexpr float k_animSpeedEpsilon = 0.1f;
    };
};

} // Gameplay

} // Platformer

