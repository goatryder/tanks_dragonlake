#include "VecInt2D.h"

const char* DirectionToString(Direction Dir)
{
	if (Dir == Direction::LEFT) return "LEFT";
	else if (Dir == Direction::RIGHT) return "RIGHT";
	else if (Dir == Direction::DOWN) return "DOWN";
	else return "UP";
}
