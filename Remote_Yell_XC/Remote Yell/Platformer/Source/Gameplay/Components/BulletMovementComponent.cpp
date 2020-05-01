#include <Gameplay/Components/BulletMovementComponent.h>

#include <Gameplay/Components/InputComponent.h>
#include <Gameplay/Components/CollisionComponent.h>
#include <Gameplay/Components/AnimRenderComponent.h>
#include <Gameplay/Components/HealthComponent.h>
#include <Gameplay/EntityFactory.h>
#include <Gameplay/EntityType.h>

#include <Utils/Math.h>
#include <float.h>

#include <iostream>

namespace Platformer
{

namespace Gameplay
{

void BulletMovementComponent::Update(const double dt)
{
    if (!myParent->IsEnabled()){ return; }
    
    Engine::Vec2 intent = { 0.0f, Constants::k_gravity };

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
    position += offset;
    transformC->SetPosition(position);
    
    // Handle Collisions
    auto myBounds = myParent->GetComponent<Engine::SystemCollisionGeometryComponent>()->GetBounds();
    
    for (auto Id : EntityFactory::DynamicEntities)
    {
        // some interaction with other characters
        if (Id != myParent->GetId()){
            auto* entity = Engine::EditEntity(Id);
            auto entityBounds = entity->GetComponent<Engine::SystemCollisionGeometryComponent>()->GetBounds();
            
            if (Engine::AABBVsAABB(myBounds, entityBounds) ){
                auto* entityHealthC = entity->SafeEditComponent<HealthComponent>();
                
                // damage correct entity
                EntityType toAttack;
                if (myType == EntityType::EntityType_Player_Bullet)
                {
                    toAttack = EntityType::EntityType_Enemy;
                }
                else
                {
                    toAttack = EntityType::EntityType_Player;
                }
                if (entityHealthC != nullptr && entityHealthC->GetEntityType() == toAttack ){
                    entityHealthC->TakeDamage(Constants::k_damage);
                    break;
                }

                break;
            }
            
        }

    }
    
    
}

void BulletMovementComponent::SetVelocity(Engine::Vec2& velocity)
{
    myVelocity = {velocity.myX, velocity.myY};
}

void BulletMovementComponent::SetType(EntityType type)
{
    myType = type;
}

EntityType BulletMovementComponent::GetEntityType() const
{
    return myType;
}

void BulletMovementComponent::ApplyPhysics(const double dt, Engine::Vec2& outMovement)
{
    myVelocity = (outMovement * Constants::k_acceleration) + (myVelocity * (1 - Constants::k_acceleration));
    outMovement = myVelocity * static_cast<float>(dt);
}

void BulletMovementComponent::ProcessCollisions(const double dt, const Engine::Vec2& desiredMove, Engine::Vec2& outOverlap)
{
    // First we check if we even need to process collision for this entity.
    auto* collisionC = myParent->SafeGetComponent<Engine::SystemTileCollisionComponent>();
    if (collisionC == nullptr)
        return;

    collisionC->CheckCollision(desiredMove, outOverlap);
    
    if (outOverlap.myX < FLT_MAX || outOverlap.myY < FLT_MAX){
        // destroy bullet on any collision
        myParent->MakeDisabled();
        Engine::Vec2 zero = {0.0f, 0.0f};
        Engine::Vec2 offscreen = {-100.0f, -100.0f};
        myVelocity = zero;
        auto* transformC = myParent->EditComponent<Engine::SystemTransformComponent>();
        transformC->SetPosition(offscreen);
    }
}

} // Gameplay

} // Platformer


