#pragma once

#include <Render/IRenderable.h>

#include <Render/DebugRenderer.h>
#include <Render/SpriteRenderer.h>

#include <map>
#include <unordered_set>

namespace Internal
{

namespace Render
{

//----------------------------------------------- 
// Drawer
//
// Controls the draw order of all drawable game components.
//
class RenderCore
{
public:

	RenderCore() = default;
	~RenderCore() = default;

	void Render();

	void AddRenderable(IRenderable* renderable);
	void RemoveRenderable(IRenderable* renderable);

	void Clear();

	DebugRenderer& EditDebugRenderer() { return myDebugRenderer; }
	SpriteRenderer& EditSpriteRenderer() { return mySpriteRenderer; }

private:

	using RenderLayer = std::unordered_set<IRenderable*>;
	std::map<RenderOrder, RenderLayer> myRenderables = {};

	SpriteRenderer mySpriteRenderer = {};
	DebugRenderer myDebugRenderer = {};

	struct Constants
	{
		static constexpr int k_defaultNumRenderables = 1000;
	};
};

} // Render

} // Internal
