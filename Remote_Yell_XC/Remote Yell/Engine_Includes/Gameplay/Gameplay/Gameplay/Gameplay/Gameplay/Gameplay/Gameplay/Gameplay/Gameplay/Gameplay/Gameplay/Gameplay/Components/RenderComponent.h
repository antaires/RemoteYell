#pragma once


#include <Gameplay/Component.h>

#include <Render/IRenderable.h>
#include <Gameplay/Component.h>

#include <Tools/SpriteSheet.h>

#include <string>

namespace Internal
{

namespace Gameplay
{

class RenderComponent : public Render::IRenderable, public Component
{
public:

	RenderComponent(Render::RenderOrder order, Render::RenderAnchor anchor = Render::RenderAnchor_TopLeft);
	RenderComponent(const char* imageFile, Render::RenderOrder order, Render::RenderAnchor anchor = Render::RenderAnchor_TopLeft);
	RenderComponent(Tools::SpriteSheet& spriteSheet, Render::RenderOrder order, Render::RenderAnchor anchor = Render::RenderAnchor_TopLeft, int drawIndex = 0);
	~RenderComponent() override;

	void Update(const double dt) override {}
	void Render() override;

protected:

	const char* myImageFile = nullptr;
	Tools::SpriteSheet* mySpriteSheet = nullptr;

	int myDrawIndex = 0;
	bool myFlipped = false;
};

} // Gameplay

} // Internal
