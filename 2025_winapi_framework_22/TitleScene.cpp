#include "pch.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "Button.h"
#include "StartButton.h"
#include "ButtonSelector.h"
#include "ExitButton.h"

void TitleScene::Init()
{
	ButtonSelector* selector = new ButtonSelector;
	selector->SetSize({ 50.f,50.f });
	AddObject(selector, Layer::UI);
	float btnpositionY = GAME_HEIGHT / 2;

	Button* button = new StartButton;
	button->SetSize({ 200.f, 50.f });
	button->SetPos({ GAME_WIDTH - button->GetSize().x / 2 - 25, btnpositionY});
	button->SetText(L"Start");

	btnpositionY += 60.0f;

	Button* exit = new ExitButton;
	exit->SetSize({ 200.f, 50.f });
	exit->SetPos({ GAME_WIDTH - button->GetSize().x / 2 - 25, btnpositionY });
	exit->SetText(L"Exit");


	AddObject(button, Layer::UI);
	AddObject(exit, Layer::UI);
	selector->AssignButton(button);
	selector->AssignButton(exit);
}
