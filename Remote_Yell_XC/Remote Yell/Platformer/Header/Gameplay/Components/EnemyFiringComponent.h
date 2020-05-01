
#pragma once

#include <Gameplay/Components/FiringComponent.h>
#include <Gameplay/MoveStateChange.h>

#include <EngineInterface.h>

namespace Platformer
{

namespace Gameplay
{

class EnemyFiringComponent : public FiringComponent
{
public:

    EnemyFiringComponent();
    ~EnemyFiringComponent() override;
    
    void Update(const double dt) override;
    const bool GetIsFiring() const;
protected:
    int firingStart = 0;
    MoveStateChange prevMoveState = MoveStateChange_None;
private:
struct Constants
{
    static constexpr float k_firepower_x = 3000.0f;
    static constexpr float k_firepower_y = 1500.0f;
    static constexpr int k_fire_rate = 25;
    static constexpr float k_forward_offset_x = 130.0f;
    static constexpr float k_backward_offset_x = 5.0f;
    static constexpr float k_straight_offset_y = 75.f;
};
};

} // Gameplay

} // Platformer

