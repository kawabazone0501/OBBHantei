#pragma once

#include <DxLib.h>
#include "Animation.h"
#include "Model.h"


class EnemyObject
{
public:
	enum class State
	{
		Wait,
		Move,
		Chase
	};

public:
	EnemyObject();

	void InitAnimation();
	void Update();
	void Draw();

	void SetIsDraw(bool is_draw_)
	{
		isDraw = is_draw_;
	}
private:
	void Wait();
	void Move();
	void Chase();

	bool IsInsideViewArea();
private:
	AnimationModel model;
	int counter;
	State currentState;

	bool isDraw;
};

