#include "DxLib.h"
#include "Model.h"
#include <math.h>
#include "Animation.h"
#include "Miku.h"
#include"Enemy.h"
#include "Camera.h"
#include"Shadow.h"
#include "SceneManager.h"


//extern Shadow g_shadow;
extern MikuObject g_Miku;
extern EnemyObject g_Enemy;

//extern int g_ShadowMapHandles[ShadowMapTypeMax];
int g_ModelHandles[MaxModelKindNum];

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true); // ウィンドウモードに設定
	SetGraphMode(800, 600, 32);	// ウィンドウのサイズ等の設定

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;				// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);	// 描画対象を裏のキャンバスに指定

	
	// カメラ設定
	SetCameraNearFar(0.1f, 1000.0f);
	SetCameraPositionAndTargetAndUpVec(
		VGet(0.0f, 10.0f, -30.0f),
		VGet(0.0f, 10.0f, 0.0f),
		VGet(0.0f, 1.0f, 0.0f)
	);

	LoadModel();

	Model Island =
	{
		VGet(0.0f, 0.0f, 0.0f),
		VGet(1.0f, 1.0f, 1.0f),
		VGet(0.0f, 0.0f, 0.0f),
		ModelKind::Island,
	};


	int stage_handle = GetModelHandle(ModelKind::Island);
	MV1SetupCollInfo(
		stage_handle,		// 当たり判定を設定するモデルのハンドル
		-1,					// 対象となるモデルのフレーム番号(-1は全て)	
		32,					// X軸の空間分割数
		32,					// Y軸の空間分割数
		32					// Z軸の空間分割数
	);


	SceneManager scene_manager(SceneBase::Type::Title);

	

	//LoadShadow();
	

	

	/*g_Miku.InitializedMiku();
	g_Enemy.InitAnimation();*/

	


	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		scene_manager.Main();

		

		ClearDrawScreen();

		//// Stageのシャドウマップの書き込み開始
		//ShadowMap_DrawSetup(g_ShadowMapHandles[(int)ShadowMapType::Stage]);

		// シャドウマップへステージモデルの描画
		//MV1DrawModel(stage_handle);

		//// Stageのシャドウマップへの描画を終了
		//ShadowMap_DrawEnd();

		//// Charaのシャドウマップの書き込み開始
		//ShadowMap_DrawSetup(g_ShadowMapHandles[(int)ShadowMapType::Chara]);

		//// Charaのシャドウマップへの描画を終了
		//ShadowMap_DrawEnd();

		DrawModel(&Island);
		

		scene_manager.Draw();

		ScreenFlip();
	}
	
	DeleteModel();
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}