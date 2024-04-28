#pragma once

#include<DxLib.h>
#include "Common.h"
#include "Collider.h"
#include "Model.h"

class MikuObject
{
public:
	VECTOR GetMikuPos();
	VECTOR GetMikuFrontVector();

	void InitializedMiku();
	void UpdateMiku();
	void DrawMiku();

	MikuObject() = delete;

	MikuObject(int handle_, Vec3 pos_) :
		modelHandle{ handle_ },
		pos{ pos_ }
	{
		InitializedMiku();
		animTime = MV1GetAnimTotalTime(modelHandle, 0);
	}

	MikuObject(int handle_, float x_, float y_, float z_) :
		modelHandle{ handle_ },
		pos{ x_,y_,z_ }
	{
		InitializedMiku();
		animTime = MV1GetAnimTotalTime(modelHandle, 0);
	}

	/*void Update();
	void Draw();*/

private:
	static const Vec3 InitColliderPos;
	static const Vec3 InitColliderScale;
	static const Vec3 InitColliderAngle;

private:
	void UpdateMatrix();

private:
	VECTOR Move01();

	int modelHandle{ -1 };
	Vec3 pos{};
	Vec3 Scale{ 1.0f,1.0f,1.0f };
	Vec3 angle{};
	MATRIX worldMat{ MGetIdent()};

	OBBCollider collider{ InitColliderPos,InitColliderScale,InitColliderAngle };

	float animTimer{ 0.0f };
	float animTime{ 0.0f };

	AnimationModel model;
};


