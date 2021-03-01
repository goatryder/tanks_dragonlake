#pragma once
#include <cstdlib>

struct VecInt2D
{
public:
	int X = 0;
	int Y = 0;

	VecInt2D() {}

	VecInt2D(const VecInt2D& Other) : X(Other.X), Y(Other.Y) {}

	VecInt2D(int InX, int InY) : X(InX), Y(InY) {}

	inline bool operator == (const VecInt2D& Other) const { return X == Other.X && Y == Other.Y; }
	inline bool operator != (const VecInt2D& Other) const { return X != Other.X || Y != Other.Y; }

	inline VecInt2D operator + (const VecInt2D& Other) const { return VecInt2D(X + Other.X, Y + Other.Y); }
	inline VecInt2D operator - (const VecInt2D& Other) const { return VecInt2D(X - Other.X, Y - Other.Y); }

	inline VecInt2D operator * (int Scalar) const { return VecInt2D(X * Scalar, Y * Scalar); }
	inline VecInt2D operator / (int Scalar) const { return VecInt2D(X / Scalar, Y / Scalar); }

	inline VecInt2D operator = (const VecInt2D& Other) { X = Other.X; Y = Other.Y; return *this; }

	inline VecInt2D GetAbs() const { return VecInt2D(std::abs(X), std::abs(Y)); }

	inline int Square() const { return X * Y; }

	/** Creates new vector with biggest X and Y values of two vectors */
	inline static VecInt2D GetMax(const VecInt2D& Vec1, const VecInt2D& Vec2) {
		return VecInt2D(Vec1.X > Vec2.X ? Vec1.X : Vec2.X, Vec1.Y > Vec2.Y ? Vec1.Y : Vec2.Y);
	}
};

enum class Direction
{
	LEFT,
	RIGHT,
	DOWN,
	UP
};

static const VecInt2D VecZero(0, 0);
static const VecInt2D VecOne(1, 1);
static const VecInt2D VecLeft(-1, 0);
static const VecInt2D VecRight(1, 0);
static const VecInt2D VecUp(0, 1);
static const VecInt2D VecDown(0, -1);

inline Direction GetDirection(VecInt2D DeltaVec)
{
	if (DeltaVec.X - DeltaVec.Y > 0)
	{
		if (std::abs(DeltaVec.X) > std::abs(DeltaVec.Y))
		{
			return Direction::RIGHT;
		}
		else
		{
			return Direction::UP;
		}
	}
	else
	{
		if (std::abs(DeltaVec.X) > std::abs(DeltaVec.Y))
		{
			return Direction::LEFT;
		}
		else
		{
			return Direction::DOWN;
		}
	}
}

inline Direction GetDirection(VecInt2D From, VecInt2D To)
{
	GetDirection(From - To);
}

inline VecInt2D DirectionToVec(Direction Dir)
{
	if (Dir == Direction::UP)
		return VecUp;
	else if (Dir == Direction::DOWN)
		return VecDown;
	else if (Dir == Direction::LEFT)
		return VecLeft;
	else if (Dir == Direction::RIGHT)
		return VecRight;
}

inline VecInt2D GetDirectionVector(VecInt2D DeltaVec)
{
	return DirectionToVec(GetDirection(DeltaVec));
}

inline VecInt2D GetDirectionVector(VecInt2D From, VecInt2D To)
{
	return DirectionToVec(GetDirection(From - To));
}

