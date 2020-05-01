#pragma once

#include <EngineInterface.h>

namespace Platformer
{

namespace Gameplay
{

enum EntityType
{
    // DYNAMIC OBJECTS
    EntityType_Player,
    EntityType_Enemy,
    EntityType_Player_Bullet,
    EntityType_Enemy_Bullet,
    // TILES
    EntityType_Tile_Ground_Mid,
    EntityType_Tile_Ground_Left,
    EntityType_Tile_Ground_Right,
    EntityType_Tile_Wall_Mid,
    EntityType_Tile_Wall_Left,
    EntityType_Tile_Wall_Right,
    EntityType_Tile_Shadow_Mid,
    EntityType_Tile_Shadow_Left,
    EntityType_Tile_Shadow_Right,
    EntityType_Tile_Water,
    EntityType_Tile_SmallBox,
    // BACKGROUND PANELS
    EntityType_Background_City,
    EntityType_Background_Clouds,
};

} // Gameplay

} // Platformer

