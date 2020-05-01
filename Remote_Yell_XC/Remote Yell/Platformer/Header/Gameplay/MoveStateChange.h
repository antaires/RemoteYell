#pragma once

#include <EngineInterface.h>

namespace Platformer
{

namespace Gameplay
{

enum MoveStateChange
{
    MoveStateChange_None,
    MoveStateChange_Jump,
    MoveStateChange_Patrol,
    MoveStateChange_Attack,
    MoveStateChange_Stalk
};

} // Gameplay

} // Platformer


