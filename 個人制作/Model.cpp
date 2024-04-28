#include <math.h>
#include <DxLib.h>
#include "Model.h"

static int g_ModelHandles[MaxModelKindNum];

bool LoadModel()
{
	const char* file_names[] =
	{
		"Res/Miku/Miku.mv1",
		"Res/Miku02/Miku.mv1",
		"Res/Floor/Floor.mv1",
	};

	for (int i = 0; i < MaxModelKindNum; i++)
	{
		g_ModelHandles[i] = MV1LoadModel(file_names[i]);
		if (g_ModelHandles[i] == -1)
		{
			return false;
		}
	}

	return true;
}

void DeleteModel()
{
	for (int i = 0; i < MaxModelKindNum; i++)
	{
		MV1DeleteModel(g_ModelHandles[i]);
	}
}

int GetModelHandle(ModelKind kind_)
{
	if (kind_<0 ||
		kind_>LastModelKindNum)
	{
		return -1;
	}

	return g_ModelHandles[kind_];
}

void DrawModel(const Model* model)
{
	if (model == nullptr)
	{
		return;
	}
	int handle = GetModelHandle(model->kind);
	VECTOR rad_angle = VScale(model->rotateAngle, (DX_PI / 180.0f));

	MV1SetPosition(handle, model->pos);
	MV1SetRotationXYZ(handle, rad_angle);
	MV1SetScale(handle, model->scale);
	MV1DrawModel(handle);
}

void DrawAnimationModel(const AnimationModel* model_)
{
	if (model_ == nullptr)
	{
		return;
	}
	int handle = GetModelHandle(model_->modelKind);
	VECTOR rad_angle = VScale(model_->rotateAngle, (DX_PI / 180.0f));

	MV1SetPosition(handle, model_->pos);
	MV1SetRotationXYZ(handle, rad_angle);
	MV1SetScale(handle, model_->scale);

	SetupDrawAnimation(handle, model_->animType, model_->animTimer);

	MV1DrawModel(handle);
}