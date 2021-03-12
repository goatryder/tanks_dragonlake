#include "PlayerTankController.h"

#include "GameMode.h"


void PlayerTankController::onKeyPressed(FRKey Key)
{
	switch (Key)
	{
	case FRKey::RIGHT:
		if (PlayerTank != nullptr) PlayerTank->MoveBegin(Direction::RIGHT);
		break;
	case FRKey::LEFT:
		if (PlayerTank != nullptr) PlayerTank->MoveBegin(Direction::LEFT);
		break;
	case FRKey::UP:
		if (PlayerTank != nullptr) PlayerTank->MoveBegin(Direction::UP);
		break;
	case FRKey::DOWN:
		if (PlayerTank != nullptr) PlayerTank->MoveBegin(Direction::DOWN);
		break;
	default:
		break;
	}
}

void PlayerTankController::onKeyReleased(FRKey Key)
{
	switch (Key)
	{
	case FRKey::RIGHT:
		if (PlayerTank != nullptr) PlayerTank->MoveEnd(Direction::RIGHT);
		break;
	case FRKey::LEFT:
		if (PlayerTank != nullptr) PlayerTank->MoveEnd(Direction::LEFT);
		break;
	case FRKey::UP:
		if (PlayerTank != nullptr) PlayerTank->MoveEnd(Direction::UP);
		break;
	case FRKey::DOWN:
		if (PlayerTank != nullptr) PlayerTank->MoveEnd(Direction::DOWN);
		break;
	default:
		break;
	}
}

void PlayerTankController::onMouseButtonClick(FRMouseButton Button, bool bIsReleased)
{
	if (Button == FRMouseButton::LEFT && !bIsReleased)
	{
		if (PlayerTank != nullptr) PlayerTank->Fire();

	}
}
