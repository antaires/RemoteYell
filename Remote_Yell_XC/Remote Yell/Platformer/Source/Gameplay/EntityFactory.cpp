#include <Gameplay/EntityFactory.h>

#include <Game.h>
#include <Level.h>

#include <Gameplay/Components/AnimRenderComponent.h>
#include <Gameplay/Components/CameraComponent.h>
#include <Gameplay/Components/FiringComponent.h>
#include <Gameplay/Components/EnemyFiringComponent.h>
#include <Gameplay/Components/InputComponent.h>
#include <Gameplay/Components/PlayerMovementComponent.h>
#include <Gameplay/Components/EnemyMovementComponent.h>
#include <Gameplay/Components/BulletMovementComponent.h>
#include <Gameplay/Components/HealthComponent.h>
#include <Gameplay/EntityType.h>

#include <Utils/ContentPipeline.h>

namespace Platformer
{

namespace Gameplay
{
Engine::EntityID_List EntityFactory::DynamicEntities;

Engine::EntityId EntityFactory::CreateEntity(EntityType type, const int x, const int y)
{
    auto& anEntity = Engine::CreateEntity();

    switch (type)
    {
        case EntityType_Player:
        {
            static const int k_camOffset = (Game::GetWindowWidth() / 2);

            const auto& pData = Utils::ContentPipeline::getContent("Resources/Data/player.json");
            Engine::SpriteSheet playerSprites("Resources/Images/player.png", pData.SpriteWidth, pData.SpriteHeight, pData.SpriteCols, pData.SpriteRows);
            Engine::AABB bounds(pData.AABBDimensions);

            anEntity
                .AddComponent<Engine::SystemTransformComponent>(x, y)
                .AddComponent<Engine::SystemCameraComponent>(k_camOffset)
                .AddComponent<Engine::SystemCollisionGeometryComponent>(bounds, pData.AABBOffset)
                .AddComponent<Engine::SystemTileCollisionComponent>()
                .AddComponent<FiringComponent>()
                .AddComponent<AnimRenderComponent>(playerSprites, pData.Animations, Engine::RenderOrder::RenderOrder_Front)
                .AddComponent<PlayerMovementComponent>()
                .AddComponent<InputComponent>()
            .AddComponent<HealthComponent>();

            anEntity.SafeEditComponent<HealthComponent>()->SetType(EntityType::EntityType_Player);
            
            DynamicEntities.push_back(anEntity.GetId());
                        
            break;
        }
        case EntityType_Enemy:
        {
            const auto& eData = Utils::ContentPipeline::getContent("Resources/Data/enemy_assault.json");
            Engine::SpriteSheet enemy_assault("Resources/Images/enemy_assault.png", eData.SpriteWidth, eData.SpriteHeight, eData.SpriteCols, eData.SpriteRows);
            Engine::AABB bounds(eData.AABBDimensions);

            anEntity
                .AddComponent<Engine::SystemTransformComponent>(x, y)
                .AddComponent<Engine::SystemCollisionGeometryComponent>(bounds, eData.AABBOffset)
                .AddComponent<Engine::SystemTileCollisionComponent>()
                .AddComponent<AnimRenderComponent>(enemy_assault, eData.Animations, Engine::RenderOrder::RenderOrder_Front)
                .AddComponent<EnemyMovementComponent>()
            .AddComponent<EnemyFiringComponent>()
            .AddComponent<HealthComponent>();
            anEntity.SafeEditComponent<HealthComponent>()->SetType(EntityType::EntityType_Enemy);
            DynamicEntities.push_back(anEntity.GetId());
            break;
        }
        case EntityType_Player_Bullet:
        {
            Engine::SpriteSheet bullet("Resources/Images/bullet_green.png", 8, 8, 1, 1);
            Engine::Vec2 AABBDimensions = { 4.0f, 4.0f };
            Engine::Vec2 AABBOffset = { 4.0f, 4.0f };
            Engine::AABB bounds(AABBDimensions);
            
            anEntity
                .AddComponent<Engine::SystemTransformComponent>(x, y)
                .AddComponent<Engine::SystemCollisionGeometryComponent>(bounds, AABBOffset)
                .AddComponent<Engine::SystemTileCollisionComponent>()
            .AddComponent<Engine::SystemRenderComponent>(bullet, Engine::RenderOrder::RenderOrder_Front)
                .AddComponent<BulletMovementComponent>();

            anEntity.SafeEditComponent<BulletMovementComponent>()->SetType(EntityType::EntityType_Player_Bullet);
            DynamicEntities.push_back(anEntity.GetId());
            break;
        }
        case EntityType_Enemy_Bullet:
        {
            Engine::SpriteSheet bullet("Resources/Images/bullet_red.png", 8, 8, 1, 1);
            Engine::Vec2 AABBDimensions = { 4.0f, 4.0f };
            Engine::Vec2 AABBOffset = { 4.0f, 4.0f };
            Engine::AABB bounds(AABBDimensions);
            
            anEntity
                .AddComponent<Engine::SystemTransformComponent>(x, y)
                .AddComponent<Engine::SystemCollisionGeometryComponent>(bounds, AABBOffset)
                .AddComponent<Engine::SystemTileCollisionComponent>()
            .AddComponent<Engine::SystemRenderComponent>(bullet, Engine::RenderOrder::RenderOrder_Front)
                .AddComponent<BulletMovementComponent>();

        anEntity.SafeEditComponent<BulletMovementComponent>()->SetType(EntityType::EntityType_Enemy_Bullet);
            DynamicEntities.push_back(anEntity.GetId());
            break;
        }
            
            
        // Backgrounds.
        case EntityType_Background_City:
        {
            Engine::SpriteSheet sheet("Resources/Images/bg_city.png", 1920, 768, 1, 1);

            anEntity.AddComponent<Engine::SystemRenderComponent>(sheet, Engine::RenderOrder::RenderOrder_NearBackground)
                    .AddComponent<Engine::SystemTransformComponent>(x, y);

            break;
        }
        case EntityType_Background_Clouds:
        {
            Engine::SpriteSheet sheet("Resources/Images/bg_clouds.png", 1920, 768, 1, 1);

            anEntity.AddComponent<Engine::SystemRenderComponent>(sheet, Engine::RenderOrder::RenderOrder_FarBackground)
                    .AddComponent<Engine::SystemTransformComponent>(x, y);

            break;
        }
        default:
            break;
    }

    return anEntity.GetId();
}

Engine::EntityId EntityFactory::CreateTile(EntityType type, const int x, const int y, bool isCollidable)
{
    auto& anEntity = Engine::CreateEntity();

    // Pick a random tile from the available tiles of this type.
    auto& indexes = Level::GetSpritesForType(type);
    auto randIdx = rand() % indexes.size();
    auto& randEl = indexes.at(randIdx);

    anEntity.AddComponent<Engine::SystemTransformComponent>(x, y)
            .AddComponent<Engine::SystemRenderComponent>(Engine::GetWorldSpritesheet(), Engine::RenderOrder::RenderOrder_Foreground, Engine::RenderAnchor::RenderAnchor_TopLeft, randEl);
                

    if (isCollidable)
    {
        Engine::AABB bounds(Engine::Vec2{ Engine::GetTileSize(), Engine::GetTileSize() } );
        anEntity.AddComponent<Engine::SystemTileCollisionComponent>()
            .AddComponent<Engine::SystemCollisionGeometryComponent>(bounds);


        const int col = x / Engine::GetTileSize();
        const int row = y / Engine::GetTileSize();

        Engine::AddCollisionTile(col, row, anEntity.GetId());
    }

    return anEntity.GetId();
}

} // Gameplay

} // Platformer

