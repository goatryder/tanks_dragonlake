#include "HUD.h"

#include "BasicUIElement.h"
#include "CountSpriteUI.h"
#include "CountNumUI.h"

#include "GameMode.h"

void HUD::InitializeHUD()
{
	for (auto& HUDElement : HUDElements)
		HUDElement->Initialize();
}

void HUD::DestroyHUD()
{
	for (auto& HUDElement : HUDElements)
		HUDElement->Destroy();

	delete this;
}

void HUD::RenderHUD()
{
	for (auto& HUDElement : HUDElements)
		HUDElement->onRender();
}

void HUD::TickHUD(unsigned int DeltaTime)
{
	for (auto& HUDElement : HUDElements)
		HUDElement->onTick(DeltaTime);
}

void HUD::AddHUDElement(BasicUIElement* NewHUDElement, bool bInitialize)
{
	HUDElements.push_back(NewHUDElement);

	if (bInitialize)
	{
		NewHUDElement->Initialize();
	}
}


DefaultHUD::DefaultHUD(BasicUIElement* WinPlate, BasicUIElement* LoosePlate, CountSpriteUI* SpawnedTankWidget, CountNumUI* PlayerRespawnNum)
	: WinPlate(WinPlate), LoosePlate(LoosePlate), SpawnedTanNumWidget(SpawnedTankWidget), PlayerRespawnNumWidget(PlayerRespawnNum)
{
	AddHUDElement(WinPlate);
	AddHUDElement(LoosePlate);
	AddHUDElement(SpawnedTankWidget);
	AddHUDElement(PlayerRespawnNum);
}

void DefaultHUD::TickHUD(unsigned int DeltaTime)
{
	if (GameModeOwner == nullptr)
		return;

	// spawned tank ui update
	TankSpawner* EnemySpawner = GameModeOwner->Level.LevelEnemyTankSpawner;

	if (EnemySpawner != nullptr)
	{
		UpdateSpawnedTankNum(EnemySpawner->GetSpawnTankNum());
	}
	else
	{
		UpdateSpawnedTankNum(SpawnedTanNumWidget->MaxNum);  // little hack
	}

	// game over plate update
	if (GameModeOwner->bGameIsOver)
	{
		ShowGameOverMsg(GameModeOwner->bIsGameOverWin);
	}
	else
	{
		HideGameOverMessage();
	}

	// Player respawn num update
	int RespawnNum = GameModeOwner->Level.PlayerRespawnNum;
	UpdatePlayerRespawnNum(RespawnNum);
}

void DefaultHUD::ShowGameOverMsg(bool bIsGameOver)
{
	if (bGameOverMessageEnabled) return;

	bGameOverMessageEnabled = true;

	if (bIsGameOver) WinPlate->Enable();
	else LoosePlate->Enable();
}

void DefaultHUD::HideGameOverMessage()
{
	if (!bGameOverMessageEnabled) return;

	bGameOverMessageEnabled = false;

	WinPlate->Disable();
	LoosePlate->Disable();
}

void DefaultHUD::UpdateSpawnedTankNum(int Num)
{
	SpawnedTanNumWidget->SetNum(Num);
}

void DefaultHUD::UpdatePlayerRespawnNum(int Num)
{
	if (Num == PlayerRespawnNumWidget->GetValue()) return;
	
	PlayerRespawnNumWidget->SetNum(Num);
}


DefaultHUD* DefaultHUD::CreateDefaultHUD()
{
	VecInt2D GameOverPos(GAME_OVER_PLATE_W, GAME_OVER_PLATE_H);
	
	BasicUIElement* WinPlate = BasicUIElement::CreateBasicUIElement(WON_UI, GameOverPos);
	BasicUIElement* LoosePlate = BasicUIElement::CreateBasicUIElement(LOOSE_UI, GameOverPos);

	VecInt2D TankUIPos(TANK_UI_FIRST_W, TANK_UI_FIRST_H);
	VecInt2D TankUIOffset(TANK_UI_OFFSET_W, TANK_UI_OFFSET_H);

	CountSpriteUI* SpawnedTanNumWidget = CountSpriteUI::CreateCountSpriteUI(TANK_ICO_UI, TankUIPos, TankUIOffset, 0,
		TANK_UI_HORIZONTAL_MAX, TANK_UI_MAX);

	VecInt2D RespawnNumPos = VecInt2D(PLAYER_RESPAWN_NUM_W, PLAYER_RESPAWN_NUM_H);
	VecInt2D NumDigitOffset = VecInt2D(UI_NUM_DIGIT_OFFSET, 0);

	CountNumUI* PlayerSpawnNum = CountNumUI::CreateCountNumUI(PLAYER_TANK_RESPAWN_NUM, 1, 1, RespawnNumPos, NumDigitOffset);

	return new DefaultHUD(WinPlate, LoosePlate, SpawnedTanNumWidget, PlayerSpawnNum);
}
