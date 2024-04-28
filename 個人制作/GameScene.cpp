#include <DxLib.h>
#include "GameScene.h"
#include "Animation.h"
#include "Miku.h"
#include"Enemy.h"
#include "Camera.h"
#include"Shadow.h"

extern MikuObject g_Miku;
extern EnemyObject g_Enemy;


void GameScene::Draw()
{
	if (CurrentStep != Step::UpDate)
	{
		return;
	}

	g_Miku.DrawMiku();
	g_Enemy.Draw();
	//DrawGraph(0, 0, bgHandle, true);
}

void GameScene::Init()
{
	bgHandle = LoadGraph("Res/Game.png");
	g_Miku.InitializedMiku();
	g_Enemy.InitAnimation();
	CurrentStep = Step::UpDate;
}

void GameScene::UpDate()
{
	if (CheckHitKey(KEY_INPUT_N))
	{
		CurrentStep = Step::Finish;
	}
	g_Miku.UpdateMiku();
	UpdateCamera();
	g_Enemy.Update();
}

SceneBase::Type GameScene::Finish()
{
	if (bgHandle != -1)
	{
		DeleteGraph(bgHandle);
	}

	return Type::Title;
}