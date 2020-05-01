
#include <Gameplay/Components/EnemyMovementComponent.h>
#include <Gameplay/Components/EnemyFiringComponent.h>
#include <Gameplay/Components/MovementComponent.h>
#include <Gameplay/Components/HealthComponent.h>
#include <Gameplay/MoveStateChange.h>
#include <Gameplay/EntityFactory.h>
#include <Gameplay/EntityType.h>
#include <random>

namespace Platformer
{

namespace Gameplay
{

MoveStateChange EnemyMovementComponent::GetMoveState() const {
    return myMoveState;
}

void EnemyMovementComponent::EvaluateMovementIntent(Engine::Vec2& outIntent, MoveStateChange& outState)
{
    if(!myParent->IsEnabled() || positionLocked ){return;}

    Engine::Vec2 playerPosition = GetPlayerPosition();
    
    auto* transformC = myParent->EditComponent<Engine::SystemTransformComponent>();
    auto myPosition = transformC->GetPosition();
    Engine::Vec2 towardsPlayer = playerPosition.operator-(myPosition);
    
    float moveSpeed = Constants::k_moveSpeed;
    if (towardsPlayer.myX > Constants::k_detectionDistance){
        outState = MoveStateChange_Patrol;
        if (patrolTimer > Constants::k_patrolClock){
            SwitchPatrolDirection();
            patrolTimer = 0;
        }
        outIntent.myX = (float) patrolDirection * moveSpeed;
        patrolTimer++;
    } else if (towardsPlayer.myX > 0 && abs(towardsPlayer.myX) > Constants::k_attackDistance ){
        outState = MoveStateChange_Stalk;
        outIntent.myX = moveSpeed;
    } else if ( towardsPlayer.myX < 0 && abs(towardsPlayer.myX) > Constants::k_attackDistance) {
        outState = MoveStateChange_Stalk;
        outIntent.myX = -moveSpeed;
    } else {
        outState = MoveStateChange_Attack;
    }
    
    if (outState == MoveStateChange_Stalk){
        float random = ((double) rand() / (RAND_MAX));
        if (random < 0.3f)
        {
            outState = MoveStateChange_Jump;
        }
    }
    
    myMoveIntent = outIntent;
    myMoveState = outState;
}

Engine::Vec2 EnemyMovementComponent::GetPlayerPosition()
{
    if ( storedPlayerId == INT_MIN){
        for (auto Id : EntityFactory::DynamicEntities)
        {
            auto* entity = Engine::EditEntity(Id);
            auto* entityHealthC = entity->SafeEditComponent<HealthComponent>();
            if (entityHealthC->GetEntityType() == EntityType::EntityType_Player ){
                storedPlayerId = Id;
                break;
            }
        }
    }
    Engine::Entity* player = Engine::EditEntity(storedPlayerId);
    auto* playerTransformC = player->SafeEditComponent<Engine::SystemTransformComponent>();
    return playerTransformC->GetPosition();
}

const Engine::Vec2 EnemyMovementComponent::GetMoveIntent() const
{
    return myMoveIntent;
}

void EnemyMovementComponent::SwitchPatrolDirection()
{
    patrolDirection *= -1;
    patrolTimer = 0;
}

void EnemyMovementComponent::SetPositionLock(bool lock)
{
    positionLocked = lock;
}


} // Gameplay

} // Platformer

