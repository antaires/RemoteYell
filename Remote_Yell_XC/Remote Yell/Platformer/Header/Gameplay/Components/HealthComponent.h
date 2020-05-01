#pragma once

#include <EngineInterface.h>
#include <Gameplay/EntityType.h>

namespace Platformer
{

namespace Gameplay
{

class HealthComponent : public Engine::Component
{
public:

    HealthComponent();
    ~HealthComponent() override;

    void Update(const double dt) override;

    const bool GetIsAlive() const;
    void TakeDamage(int damage);
    void SetType(EntityType type);
    EntityType GetEntityType() const;
protected:
    int myHealth = 50;
    bool isAlive = true;
    EntityType myType;
private:
    struct Constants
    {
        static constexpr int k_start_health = 50;
    };
};

} // Gameplay

} // Platformer


