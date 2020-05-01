#pragma once


namespace Internal
{

namespace Gameplay
{

class Entity;

class  Component
{
public:

	Component() {}
	virtual ~Component() {}

	virtual void OnActivated() {}
	virtual void Update(const double dt) = 0;
	virtual void OnDeactivated() {}

protected:

	friend class Entity;

	Entity* myParent;
};

} // Gameplay

} // Internal
