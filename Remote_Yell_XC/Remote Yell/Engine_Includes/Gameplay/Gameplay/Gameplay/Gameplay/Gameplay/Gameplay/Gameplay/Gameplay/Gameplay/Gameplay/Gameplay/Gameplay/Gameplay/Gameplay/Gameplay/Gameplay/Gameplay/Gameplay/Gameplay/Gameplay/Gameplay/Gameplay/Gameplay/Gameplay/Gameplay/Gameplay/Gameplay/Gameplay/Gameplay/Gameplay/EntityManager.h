#pragma once

#include <Gameplay/Entity.h>

#include <map>
#include <unordered_map>

namespace Internal
{

namespace Gameplay
{

class EntityManager
{
public:

	EntityManager() = default;
	~EntityManager();

	void Update(const double dt);
	void UnloadAll();

	Entity& CreateEntity();

	const Entity* GetEntity(EntityId id) const;
	Entity* EditEntity(EntityId id);

private:
	void PreUpdate();
	void PostUpdate();

	static int theEntityCounter;

	using EntityMap = std::unordered_map<EntityId, Entity>;
	EntityMap myEntities = {};
};

class EntityID_List : public std::vector<EntityId>
{};

} // Gameplay

} // Internal
