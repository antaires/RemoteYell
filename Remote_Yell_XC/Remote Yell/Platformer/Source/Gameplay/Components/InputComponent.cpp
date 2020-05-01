#include <Gameplay/Components/InputComponent.h>

#include <cassert>
#include <vector>

namespace Platformer
{

namespace Gameplay
{

InputComponent::InputComponent()
{
    std::vector<const char*> validKeys = { "w", "a", "s", "d", "up", "left", "down", "right", "space", "left shift", "r" };
    for (auto& key : validKeys)
    {
        myKeyStates[key] = KeyState {};
    }
}

void InputComponent::Update(const double dt)
{
    for (auto& keyEntry : myKeyStates)
    {
        auto& key = keyEntry.first;
        auto& keyState = keyEntry.second;

        keyState.Was = keyState.Is;

        keyState.Is = Engine::KeyDown(key);
    }
}

const bool InputComponent::KeyPressed(const char* key) const
{
    assert(myKeyStates.count(key) > 0);
    auto& keyState = myKeyStates.at(key);
    return (!keyState.Was && keyState.Is);
}

const bool InputComponent::KeyDown(const char* key) const
{
    assert(myKeyStates.count(key) > 0);
    auto& keyState = myKeyStates.at(key);
    return keyState.Is;
}

const bool InputComponent::KeyUp(const char* key) const
{
    assert(myKeyStates.count(key) > 0);
    auto& keyState = myKeyStates.at(key);
    return !keyState.Is;
}

} // Gameplay

} // Platformer

