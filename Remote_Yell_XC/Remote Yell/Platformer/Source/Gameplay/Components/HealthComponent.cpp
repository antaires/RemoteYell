#include <EngineInterface.h>
#include <Gameplay/Components/HealthComponent.h>
#include <Gameplay/Components/EnemyFiringComponent.h>
#include <Gameplay/Components/EnemyMovementComponent.h>
#include <Gameplay/EntityType.h>

namespace Platformer
{

namespace Gameplay
{

HealthComponent::HealthComponent()
{
}

HealthComponent::~HealthComponent()
{
}

void HealthComponent::Update(const double dt) {}

void HealthComponent::TakeDamage(int damage){
    myHealth -= damage;
    if (myHealth < 0){
        isAlive = false;
        
        // lock gun and position
        if (myType == EntityType_Enemy){
            auto* firingC = myParent->SafeEditComponent<FiringComponent>();
            firingC->SetGunLock(true);
            
            auto* positionC = myParent->SafeEditComponent<EnemyMovementComponent>();
            positionC->SetPositionLock(true);
        }
        
        myParent->MakeDisabled();
    }
}

void HealthComponent::SetType(EntityType type)
{
    myType = type;
}

EntityType HealthComponent::GetEntityType() const {
    return myType;
}

const bool HealthComponent::GetIsAlive() const { return isAlive; }

} // Gameplay

} // Platformer

