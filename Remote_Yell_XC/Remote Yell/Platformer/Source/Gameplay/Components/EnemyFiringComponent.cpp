#include <Gameplay/Components/FiringComponent.h>
#include <Gameplay/Components/EnemyFiringComponent.h>
#include <Gameplay/Components/AnimRenderComponent.h>
#include <Gameplay/Components/EnemyMovementComponent.h>
#include <Gameplay/Components/BulletMovementComponent.h>
#include <Gameplay/EntityFactory.h>
#include <Gameplay/MoveStateChange.h>


#include <iostream>

namespace Platformer
{

namespace Gameplay
{

EnemyFiringComponent::EnemyFiringComponent()
{
}

EnemyFiringComponent::~EnemyFiringComponent()
{
}

void EnemyFiringComponent::Update(const double dt)
{
    if (!myParent->IsEnabled() || gunLocked){ return;}
    
    auto* parentMoveC = myParent->GetComponent<EnemyMovementComponent>();
    auto enemyMoveState = parentMoveC->GetMoveState();
    
    auto* parentAnimCompC = myParent->GetComponent<AnimRenderComponent>();
    isForward = !(parentAnimCompC->GetIsFlipped());

    // start firing rate count
    myIsFiring = enemyMoveState == MoveStateChange::MoveStateChange_Attack || MoveStateChange::MoveStateChange_Jump;
    if (myIsFiring && prevMoveState != enemyMoveState){
        firingStart = 0;
    }

    // Firing.
    if (myIsFiring && (firingStart > Constants::k_fire_rate)){
        firingStart = 0;
        auto* transformC = myParent->GetComponent<Engine::SystemTransformComponent>();
        auto& position = transformC->GetPosition();

        Engine::Vec2 velocity = {Constants::k_firepower_x, 0.0f};
        Engine::Vec2 offset = {0.0f, Constants::k_straight_offset_y};
        
        // shoot forward or backward?
        if (isForward){
            offset.myX = Constants::k_forward_offset_x;
        } else {
            velocity.myX *= -1;
            offset.myX = Constants::k_backward_offset_x;
        }
        
        Engine::Vec2 start = {position.myX + offset.myX, position.myY + offset.myY};
        FireBullet(start, velocity, EntityType_Enemy_Bullet);
        
    }
    prevMoveState = enemyMoveState;
    firingStart += 1;
}

const bool EnemyFiringComponent::GetIsFiring() const
{
    return myIsFiring;
}

} // Gameplay

} // Platformer


