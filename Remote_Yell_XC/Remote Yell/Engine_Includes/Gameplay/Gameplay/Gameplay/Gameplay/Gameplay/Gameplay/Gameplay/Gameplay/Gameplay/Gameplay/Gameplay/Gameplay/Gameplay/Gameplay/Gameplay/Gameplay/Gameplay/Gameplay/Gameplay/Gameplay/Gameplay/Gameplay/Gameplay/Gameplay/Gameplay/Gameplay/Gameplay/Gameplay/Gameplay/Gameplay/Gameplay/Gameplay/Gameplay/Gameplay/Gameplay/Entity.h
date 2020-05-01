#pragma once

#include <cassert>
#include <vector>

namespace Internal
{

namespace Gameplay
{

using EntityId = int;

class Component;

class  Entity
{
public:

	Entity(EntityId id);
	~Entity();

	// component operations
	template <typename T>
	const T* SafeGetComponent() const;

	template <typename T>
	const T* GetComponent() const;

	template <typename T>
	T* SafeEditComponent();

	template <typename T>
	T* EditComponent();

	template <typename T, typename ... Ts>
	Entity& AddComponent(Ts... args);


	// callbacks
	void OnEnabled();
	void Update(const double dt);
	void OnDisabled();


	// Entity operations
	void MakeEnabled();
	void MakeDisabled ();

	const EntityId GetId() const { return myId; }

	const bool IsMarkedForDelete() const { return myMarkedForDelete; }
	bool HasStatusChanged() const { return myStatusChanged; }
	bool IsEnabled() const { return myEnabled; }

	void MarkForDelete() { myMarkedForDelete = true;  }
private:

	EntityId myId;
	std::vector<Component*> myComponents;
	bool myStatusChanged = false;
	bool myMarkedForDelete = false;
	bool myEnabled = true;
};

template <typename T>
const T* Entity::SafeGetComponent() const
{
	for (const Component* component : myComponents)
		if (const T* t = dynamic_cast<const T*>(component))
			return t;
	return nullptr;
}

template <typename T>
const T* Entity::GetComponent() const
{
	const T* t = SafeGetComponent<T>();
	assert(t && "Entity does not contain a component of type T");
	return t;
}

template <typename T>
T* Entity::SafeEditComponent()
{
	for (Component* component : myComponents)
		if (T* t = dynamic_cast<T*>(component))
			return t;
	return nullptr;
}

template <typename T>
T* Entity::EditComponent()
{
	T* t = SafeEditComponent<T>();
	assert(t && "Entity does not contain a component of type T");
	return t;
}

template <typename T, typename ... Ts>
Entity& Entity::AddComponent(Ts... args)
{
	T* newComponent = new T(args...);
	myComponents.push_back(newComponent);

	newComponent->myParent = this;
	
	return *this;
}

} // Gameplay

} // Internal
