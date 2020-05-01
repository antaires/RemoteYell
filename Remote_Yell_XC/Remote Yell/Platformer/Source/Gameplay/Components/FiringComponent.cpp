#include <Gameplay/Components/FiringComponent.h>
#include <Gameplay/Components/InputComponent.h>
#include <Gameplay/Components/BulletMovementComponent.h>
#include <Gameplay/EntityFactory.h>

#include <iostream>

namespace Platformer
{

namespace Gameplay
{

FiringComponent::FiringComponent()
{
}

FiringComponent::~FiringComponent()
{
}

void FiringComponent::Update(const double dt)
{
    auto* inputC = myParent->GetComponent<InputComponent>();
    
    if (inputC->KeyDown("w"))
    {
        myAiming = Aiming_DiagUp;
    }
    else if (inputC->KeyDown("s"))
    {
        myAiming = Aiming_DiagDown;
    }
    else
    {
        myAiming = Aiming_Straight;
    }
    myIsFiring = Engine::MouseLeftDown();
    if (!Engine::MouseLeftDown()){
        hasFired = false;
    }
    
        
    if (inputC->KeyDown("a"))
    {
        isForward = false;
    } else if (inputC->KeyDown("d"))
    {
        isForward = true;
    }
    
    
    bool isJumping = inputC->KeyDown("space");

    // Firing.
    if (myIsFiring && !hasFired){
        hasFired = true;
        auto* transformC = myParent->GetComponent<Engine::SystemTransformComponent>();
        auto& position = transformC->GetPosition();

        // match bullet to gun
        Engine::Vec2 velocity = {Constants::k_firepower_x, 0.0f};
        Engine::Vec2 offset = {0.0f, Constants::k_straight_offset_y};
        if (isForward){
            offset.myX = Constants::k_forward_offset_x;
        } else {
            velocity.myX *= -1;
            offset.myX = Constants::k_backward_offset_x;
        }
        if (!isJumping && myAiming == Aiming_DiagUp){
             velocity.myY = -Constants::k_firepower_y;
            offset.myY = Constants::k_up_offset_y;
        } else if (!isJumping && myAiming == Aiming_DiagDown){
            velocity.myY = Constants::k_firepower_y;
            offset.myY = Constants::k_down_offset_y;
        }
        
        Engine::Vec2 start = {position.myX + offset.myX, position.myY + offset.myY};
        FireBullet(start, velocity, EntityType_Player_Bullet);
    }

}

void FiringComponent::FireBullet(Engine::Vec2& position, Engine::Vec2& velocity, EntityType type)
{
    Engine::EntityId bulletId = EntityFactory::CreateEntity(type, position.myX, position.myY);
    auto* bullet = Engine::EditEntity(bulletId);
    auto* bulletMovementC = bullet->SafeEditComponent<BulletMovementComponent>();
    bulletMovementC->SetVelocity(velocity);
}


void FiringComponent::SetGunLock(bool isLocked)
{
    gunLocked = isLocked;
}

bool FiringComponent::GetIsGunLocked() const
{
    return gunLocked;
}

} // Gameplay

} // Platformer

