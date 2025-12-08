#include "pch.h"
#include "SceneManager.h"
#include "StartButton.h"

void StartButton::OnClick()
{
	GET_SINGLE(SceneManager)->LoadScene(L"DevScene");
}
