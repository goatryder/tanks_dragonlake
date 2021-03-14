#pragma once

#include <vector>

class BasicUIElement;
class CountSpriteUI;
class CountNumUI;
class GameMode;

class HUD
{
public:

	HUD() {}
	~HUD() {}

	GameMode* GameModeOwner = nullptr;

	void AddHUDElement(BasicUIElement* NewHUDElement, bool bInitialize = false);

	virtual void InitializeHUD();
	virtual void DestroyHUD();

	virtual void RenderHUD();
	virtual void TickHUD(unsigned int DeltaTime);

protected:

	std::vector<BasicUIElement*> HUDElements = {};

};

class DefaultHUD : public HUD
{
public:
	
	DefaultHUD(BasicUIElement* WinPlate, BasicUIElement* LoosePlate, CountSpriteUI* SpawnedTankWidget, CountNumUI* PlayerRespawnNum);
	~DefaultHUD() {}

	virtual void TickHUD(unsigned int DeltaTime) override;
	
protected:

	BasicUIElement* WinPlate;
	BasicUIElement* LoosePlate;
	CountSpriteUI* SpawnedTanNumWidget;
	CountNumUI* PlayerRespawnNumWidget;

	void ShowGameOverMsg(bool bIsGameOver);
	void HideGameOverMessage();
	void UpdateSpawnedTankNum(int Num);
	void UpdatePlayerRespawnNum(int Num);

	bool bGameOverMessageEnabled = false;

public:

	static DefaultHUD* CreateDefaultHUD();
};