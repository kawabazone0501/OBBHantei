#pragma once

#include<DxLib.h>
#include "Animation.h"

enum ModelKind
{
	Miku,
	Miku02,
	Island,
};

struct Model
{
	VECTOR pos;
	VECTOR scale;
	VECTOR rotateAngle;
	ModelKind kind;
};

struct AnimationModel
{
	VECTOR pos;
	VECTOR scale;
	VECTOR rotateAngle;
	ModelKind modelKind;

	VECTOR frontVector;
	float animTimer;
	float animTime;
	AnimType animType;
};

const int LastModelKindNum = ModelKind::Island;
const int MaxModelKindNum = ModelKind::Island + 1;

bool LoadModel();
void DrawModel(const Model* model_);
void DrawAnimationModel(const AnimationModel* model_);
void DeleteModel();
int GetModelHandle(ModelKind kind_);