#pragma once

#include <Gameplay/Component.h>

#include <Math/Vec2.h>

namespace Internal
{

namespace Gameplay
{

class TransformComponent : public Component
{
public:

	TransformComponent(const int x, const int y)
		: myPosition(x, y)
	{}
	~TransformComponent() override = default;

	// Positions are updated externally.
	void Update(const double dt) override {}

	const Math::Vec2& GetPosition() const { return myPosition; }
	void SetPosition(const Math::Vec2& pos) { myPosition = pos; }

private:

	Math::Vec2 myPosition;
};

} // Gameplay

} // Internal
