#include "RenderBase.h"

Wall* WallInstance = new Wall();
RenderBase* RenderBase::Wall = WallInstance;

VecInt2D GetAnchorOffset(VecInt2D Size, Anchor Anchor)
{
	VecInt2D Offset(0, 0);

	switch (Anchor)
	{
	case Anchor::CENTER:
		Offset = Size / 2;
		break;
	case Anchor::TOP_RIGHT:
		Offset.X = Size.X;
		break;
	case Anchor::BOTTOM_LEFT:
		Offset.Y = Size.Y;
		break;
	case Anchor::BOTTOM_RIGHT:
		Offset = Size;
		break;
	case Anchor::TOP:
		Offset.X = Size.X / 2;
		break;
	case Anchor::BOTTOM:
		Offset.X = Size.X / 2;
		Offset.Y = Size.Y;
		break;
	case Anchor::LEFT:
		Offset.Y = Size.Y / 2;
		break;
	case Anchor::RIGHT:
		Offset.X = Size.X;
		Offset.Y = Size.Y / 2;
		break;
	default: // Anchor::TOP_LEFT
		break;
	}

	return Offset;
}

void Wall::onRender()
{
}
