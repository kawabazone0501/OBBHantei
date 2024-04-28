#pragma once
#include <DxLib.h>
#include "SceneBase.h"

class TitleScene :public SceneBase
{
public:
	TitleScene():bgHandle(-1)
	{
	}

	~TitleScene() override
	{
		if (bgHandle != -1)
		{
			DeleteGraph(bgHandle);
		}
	}

	virtual void Draw()override;
	Type GetType() override
	{
		return Type::Title;
	}

private :
	void Init() override;
	void UpDate() override;
	Type Finish() override;

	int bgHandle;
};

//void InitTitleScene();		//タイトルシーンの初期化
//void RunTitleScene();		//タイトルシーンの（メイン処理の）実行
//void FinishTitleScene();	//タイトルシーンの終了
//
//void MainTitleScene();