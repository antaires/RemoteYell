#pragma once

#include <EngineInterface.h>
#include <Gameplay/EntityType.h>

namespace Platformer
{

namespace Gameplay
{

class Entity;

struct EntityFactory
{
    static Engine::EntityId CreateEntity(EntityType type, const int x, const int y);

    static Engine::EntityId CreateTile(EntityType type, const int x, const int y, bool isCollidable);
    
    static Engine::EntityID_List DynamicEntities;
};


} // Gameplay

} // Platformer

