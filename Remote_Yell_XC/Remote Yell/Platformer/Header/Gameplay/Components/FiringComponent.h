#pragma once

#include <EngineInterface.h>
#include <Gameplay/EntityType.h>


namespace Platformer
{

namespace Gameplay
{

enum AimDirection
{
    Aiming_Straight,
    Aiming_DiagUp,
    Aiming_DiagDown
};

class FiringComponent : public Engine::Component
{
public:

    FiringComponent();
    ~FiringComponent() override;

    void Update(const double dt) override;

    const AimDirection GetAimDirection() const { return myAiming; }
    const bool GetIsFiring() const { return myIsFiring; }
    void SetGunLock(bool isLocked);
    bool GetIsGunLocked() const;
    bool isForward = true;

protected:
    AimDirection myAiming = Aiming_Straight;
    void FireBullet(Engine::Vec2& position, Engine::Vec2& velocity, EntityType type);
    bool myIsFiring = false;
    bool hasFired = false;
    bool gunLocked = false;
private:
    struct Constants
    {
        static constexpr float k_firepower_x = 3000.0f;
        static constexpr float k_firepower_y = 1500.0f;
        static constexpr float k_forward_offset_x = 130.0f;
        static constexpr float k_backward_offset_x = 5.0f;
        static constexpr float k_straight_offset_y = 90.f;
        static constexpr float k_up_offset_y = 50.0f;
        static constexpr float k_down_offset_y = 140.0f;
    };
};

} // Gameplay

} // Platformer

