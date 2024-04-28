#include <DxLib.h>
#include "TitleScene.h"
#include "Common.h"

extern SceneStep g_currentSceneStep;
extern SceneType g_currentSceneType;
int g_Handles[TexturKind::TexturKindMax];

void TitleScene::Draw()
{
	if (CurrentStep != Step::UpDate)
	{
		return;
	}

	DrawGraph(0, 0, bgHandle, true);
}

void TitleScene::Init()
{
	bgHandle = LoadGraph("Res/Title.png");

	CurrentStep = Step::UpDate;
}

void TitleScene::UpDate()
{
	if (CheckHitKey(KEY_INPUT_B))
	{
		CurrentStep = Step::Finish;
	}
}

SceneBase::Type TitleScene::Finish()
{
	if (bgHandle != -1)
	{
		DeleteGraph(bgHandle);
	}

	return Type::Game;
}