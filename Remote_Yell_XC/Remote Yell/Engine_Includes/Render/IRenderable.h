#pragma once


namespace Internal
{

namespace Render
{

// Forward declare for friend.
class RenderCore;

enum RenderOrder
{
	RenderOrder_FarBackground = 0,
	RenderOrder_NearBackground,
	RenderOrder_Mid,
	RenderOrder_Foreground,
	RenderOrder_Front,
	RenderOrder_UI,

	RenderOrder_Count
};

enum RenderAnchor
{
	RenderAnchor_TopLeft = 0,
	RenderAnchor_Center,
};

class IRenderable
{
public:

	IRenderable(RenderOrder order, RenderAnchor anchor = RenderAnchor_TopLeft);
	virtual ~IRenderable();

	virtual void Render() = 0;

protected:

	friend class RenderCore;

	RenderOrder myRenderOrder = RenderOrder_FarBackground;
	RenderAnchor myRenderAnchor = RenderAnchor_TopLeft;
};

} // Render

} // Internal