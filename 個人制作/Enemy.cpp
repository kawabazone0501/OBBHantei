#include <math.h>
#include <DxLib.h>
#include "Model.h"
#include "Enemy.h"
#include "Miku.h"

EnemyObject g_Enemy;

extern MikuObject g_Miku;

EnemyObject::EnemyObject()
{
	model.pos = VGet(10.0f, 0.0f, 10.0f);
	model.scale = VGet(0.5f, 0.5f, 0.5f);
	model.rotateAngle = VGet(0.0f, 0.0f, 0.0f);
	model.modelKind = ModelKind::Miku02;
	model.animTimer = 0.0f;
	model.animTime = 0.0f;
	model.animType = AnimType::Wait;
	model.frontVector = VGet(0.0f, 0.0f, -1.0f);

	counter = 0;
	currentState = State::Wait;

	isDraw = true;
}

void EnemyObject::InitAnimation()
{
	ChangeAnimation(GetModelHandle(model.modelKind), AnimType::Wait, model.animType, model.animTimer, model.animTime);
}

void EnemyObject::Update()
{
	switch (currentState)
	{
	case EnemyObject::State::Wait:
		Wait();
		break;
	case EnemyObject::State::Move:
		Move();
		break;
	case EnemyObject::State::Chase:
		Chase();
		break;
	}

	if (PlayAnimation(model.animTimer, model.animTime) == true)
	{
		// タイマーをリセット
		model.animTimer = 0.0f;
	}
}

void EnemyObject::Draw()
{
	if (isDraw == true)
	{
		DrawAnimationModel(&model);
	}
}

void EnemyObject::Wait()
{
	counter++;
	int change_count = 120;
	if (counter >= change_count)
	{
		counter = 0;	
		currentState = State::Move;
		
		model.rotateAngle.y = rand() % 360;
		ChangeAnimation(GetModelHandle(model.modelKind), AnimType::Run, model.animType, model.animTimer, model.animTime);
	}
	else if (IsInsideViewArea() == true)
	{
		currentState = State::Chase;
		ChangeAnimation(GetModelHandle(model.modelKind), AnimType::Run, model.animType, model.animTimer, model.animTime);
	}
}

void EnemyObject::Move()
{
	float rad = model.rotateAngle.y * (DX_PI / 180.0f);
	VECTOR vec = VGet(
		sinf(rad),
		0.0f,
		cosf(rad)
	);
	vec = VScale(vec, -1.0f);
	float move_speed = 0.1f;
	vec = VScale(vec, move_speed);

	VECTOR new_pos = VAdd(vec, model.pos);
	new_pos.y += 1.0f;

	MV1_COLL_RESULT_POLY result = MV1CollCheck_Line(
		GetModelHandle(ModelKind::Island),				
		-1,												
		new_pos,										
		VGet(new_pos.x, new_pos.y - 100.0f, new_pos.z)	
	);

	if (result.HitFlag == 1) 
	{
		new_pos.y = result.HitPosition.y;
		model.pos = new_pos;
		if (IsInsideViewArea() == true)
		{
			currentState = State::Chase;
		}
	}

	counter++;
	int change_count = 120;

	if (counter >= change_count)
	{
		currentState = State::Wait;
		counter = 0;
		ChangeAnimation(GetModelHandle(model.modelKind), AnimType::Wait, model.animType, model.animTimer, model.animTime);
	}
	else if (IsInsideViewArea() == true)
	{
		currentState = State::Chase;
	}
}

void EnemyObject::Chase()
{
	VECTOR player_pos = g_Miku.GetMikuPos();
	VECTOR enemy_to_player = VSub(player_pos, model.pos);

	float length = sqrtf(enemy_to_player.x * enemy_to_player.x +
		enemy_to_player.z * enemy_to_player.z);
	if (length <= 0.0f)
	{
		return;
	}
	VECTOR normal = VGet(enemy_to_player.x / length, 0.0f, enemy_to_player.z / length);

	float move_speed = 0.1f;
	VECTOR velocity = VScale(normal, move_speed);

	VECTOR new_pos = VAdd(velocity, model.pos);
	new_pos.y += 1.0f;
	MV1_COLL_RESULT_POLY result = MV1CollCheck_Line(
		GetModelHandle(ModelKind::Island),				
		-1,												
		new_pos,										
		VGet(new_pos.x, new_pos.y - 100.0f, new_pos.z)	
	);

	if (result.HitFlag == 1) 
	{
		new_pos.y = result.HitPosition.y;

		model.pos = new_pos;
	}

	float rad = atan2f(-velocity.x, -velocity.z);
	model.rotateAngle.y = rad * (180.0f / DX_PI);

	if (IsInsideViewArea() == false)
	{
		currentState = State::Wait;
		counter = 0;
		ChangeAnimation(GetModelHandle(model.modelKind), AnimType::Wait, model.animType, model.animTimer, model.animTime);
	}
}

bool EnemyObject::IsInsideViewArea()
{
	VECTOR vec = VSub(g_Miku.GetMikuPos(), model.pos);
	float length = sqrtf(vec.x * vec.x + vec.z * vec.z);

	float radius = 10.0f;
	if (length <= radius)
	{
		return true;
	}

	return false;
}