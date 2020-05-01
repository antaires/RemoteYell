#pragma once

#include <EngineInterface.h>

#include <map>

namespace Platformer
{

namespace Gameplay
{

class InputComponent : public Engine::Component
{
public:

    InputComponent();
    ~InputComponent() override = default;

    void Update(const double dt) override;

    const bool KeyPressed(const char* key) const;
    const bool KeyDown(const char* key) const;
    const bool KeyUp(const char* key) const;

private:

    struct KeyState
    {
        bool Was = false;
        bool Is = false;
    };

    std::map<const char*, KeyState> myKeyStates = {};
};

} // Gameplay

} // Platformer

