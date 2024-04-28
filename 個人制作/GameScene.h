#pragma once
#include <DxLib.h>
#include "SceneBase.h"

class GameScene :public SceneBase
{
public:
	GameScene():bgHandle(-1)
	{
	}

	~GameScene()override
	{
		if (bgHandle != -1)
		{
			DeleteGraph(bgHandle);
		}
	}

	virtual void Draw()override;
	Type GetType() override
	{
		return Type::Game;
	}

protected:
	void Init() override;
	void UpDate() override;
	Type Finish() override;

private:

	int bgHandle;
};