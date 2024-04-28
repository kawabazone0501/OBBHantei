#include <DxLib.h>
#include "TitleScene.h"
#include "Common.h"

extern SceneStep g_currentSceneStep;
extern SceneType g_currentSceneType;
int g_Handles[TexturKind::TexturKindMax];

//タイトルシーンを動かす関数
//void MainTitleScene()
//{
//	switch (g_currentSceneStep)
//	{
//	case SceneStep::SceneStepInit:
//		InitTitleScene();
//		break;
//	case SceneStep::SceneStepRun:
//		RunTitleScene();
//		break;
//	case SceneStep::SceneStepFinish:
//		FinishTitleScene();
//		break;
//	}
//}
//
//void InitTitleScene()
//{
//	g_Handles[TexturKind::TexturKindTitle] = LoadGraph("Res/Title.png");
//
//	g_currentSceneStep = SceneStepRun;
//}
//
//void RunTitleScene()
//{
//	ClearDrawScreen();
//	DrawGraph(0, 0, g_Handles[TexturKind::TexturKindTitle], true);
//	if (CheckHitKey(KEY_INPUT_RETURN))
//	{
//		g_currentSceneStep = SceneStepFinish;
//	}
//	ScreenFlip();
//}

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