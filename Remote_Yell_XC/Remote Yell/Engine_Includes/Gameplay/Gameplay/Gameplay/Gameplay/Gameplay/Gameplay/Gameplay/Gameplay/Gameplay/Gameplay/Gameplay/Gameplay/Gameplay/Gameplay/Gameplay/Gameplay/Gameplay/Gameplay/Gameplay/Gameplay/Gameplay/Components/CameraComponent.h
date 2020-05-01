#pragma once


#include <Gameplay/Component.h>

namespace Internal
{

namespace Gameplay
{

class CameraComponent : public Component
{
public:

	CameraComponent(const int camOffset);
	~CameraComponent() override = default;

	void Update(const double dt) override;

private:

	int myCamOffset;
};

} // Gameplay

} // Internal
