#include "RenderBase.h"

Wall* WallInstance = new Wall();
RenderBase* RenderBase::Wall = WallInstance;

VecInt2D GetAnchorOffset(VecInt2D Size, Anchor Anchor)
{
	VecInt2D Offset;

	switch (Anchor)
	{
	case Anchor::CENTER:
		Offset = Size / 2;
		break;
	case Anchor::TOP_RIGHT:
		Offset = VecInt2D(Size.X, 0);
		break;
	case Anchor::BOTTOM_LEFT:
		Offset = VecInt2D(0, Size.Y);
		break;
	case Anchor::BOTTOM_DOWN:
		Offset = Size;
		break;
	default:
		break;
	}

	return Offset;
}

void Wall::onRender()
{
}
