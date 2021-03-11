#pragma once

class Tank;

enum class FRMouseButton;
enum class FRKey;

class GameMode;

class PlayerTankController
{
public:
	PlayerTankController() {}
	PlayerTankController(Tank* PlayerTank, GameMode* GameModeOwner) : PlayerTank(PlayerTank), GameModeOwner(GameModeOwner) {}
	~PlayerTankController() {}

	Tank* PlayerTank = nullptr;
	GameMode* GameModeOwner = nullptr;

	void onKeyPressed(FRKey Key);
	void onKeyReleased(FRKey Key);
	void onMouseButtonClick(FRMouseButton Button, bool bIsReleased);
};