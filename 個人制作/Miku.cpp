#include <math.h>
#include <DxLib.h>
#include "Model.h"
#include "Miku.h"
#include "Common.h"
#include "Collider.h"
#include "Collision.h"

const Vec3 MikuObject::InitColliderPos{ 0.0f, 0.0f, 0.0f };
const Vec3 MikuObject::InitColliderScale{ 80.0f, 10.0f, 10.0f };
const Vec3 MikuObject::InitColliderAngle{ 0.0f, 0.0f, 0.0f };

//MikuObject g_Miku;

static int g_ModelHandles[MaxModelKindNum];

MikuObject g_Miku(g_ModelHandles[0], VGet(0.0f, 0.0f, 0.0f));

VECTOR MikuObject::GetMikuPos()
{
	return model.pos;
}

VECTOR MikuObject::GetMikuFrontVector()
{
	return model.frontVector;
}

void MikuObject::InitializedMiku()
{
	model.pos = VGet(10.0f, 10.0f, 0.0f);
	model.scale = VGet(0.5f, 0.5f, 0.5f);
	model.rotateAngle = VGet(0.0f, 0.0f, 0.0f);
	model.modelKind = ModelKind::Miku;
	model.animTimer = 0.0f;
	model.animTime = 0.0f;
	model.animType = AnimType::Wait;
	model.frontVector = VGet(0.0f, 0.0f, -1.0f);


	ChangeAnimation(GetModelHandle(model.modelKind), AnimType::Wait, model.animType, model.animTimer, model.animTime);
}

void MikuObject::UpdateMiku()
{
	float roate_speed = 3.0f;
	float add_rotate = 0.0f;
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		add_rotate -= roate_speed;
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		add_rotate += roate_speed;
	}

	if (add_rotate != 0.0f)
	{
		model.rotateAngle.y += add_rotate;

		float rad = model.rotateAngle.y * (DX_PI / 180.0f);
		float front_vec_x = -sinf(rad);
		float front_vec_y = -cosf(rad);
		model.frontVector = VGet(front_vec_x, 0.0f, front_vec_y);
	}

	float move_speed = 0.5f;
	//移動キー入力
	if (CheckHitKey(KEY_INPUT_UP))
	{
		VECTOR new_pos = Move01();
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

		if (model.animType != AnimType::Run)
		{
			ChangeAnimation(GetModelHandle(model.modelKind), AnimType::Run, model.animType, model.animTimer, model.animTime);
		}
	}
	else
	{
		if (model.animType != AnimType::Wait)
		{
			ChangeAnimation(GetModelHandle(model.modelKind), AnimType::Wait, model.animType, model.animTimer, model.animTime);

		}
	}

	if (PlayAnimation(model.animTimer, model.animTime) == true)
	{
		// タイマーをリセット
		model.animTimer = 0.0f;
	}
	UpdateMatrix();
}

void MikuObject::DrawMiku()
{
	DrawAnimationModel(&model);

#if defined (DEBUG)
	collider.Draw();
#endif
}

void MikuObject::UpdateMatrix()
{
	// 親行列を作るためにモデル情報を最新に更新する
	worldMat = MGetIdent();
	MATRIX scale_mat = MGetIdent();
	CreateScalingMatrix(&scale_mat, Scale.x, Scale.y, Scale.z);
	MATRIX rotate_mat = MGetIdent();
	VECTOR angle_rad = angle.ToVECTOR();
	angle_rad = VScale(angle_rad, DX_PI / 180.0f);
	CreateRotationXYZMatrix(&rotate_mat, angle_rad.x, angle_rad.y, angle_rad.z);
	MATRIX translate_mat = MGetIdent();
	CreateTranslationMatrix(&translate_mat, pos.x, pos.y, pos.z);
	worldMat = MMult(worldMat, scale_mat);
	worldMat = MMult(worldMat, rotate_mat);
	worldMat = MMult(worldMat, translate_mat);
	MV1SetMatrix(modelHandle, worldMat);

	/*
		MV1GetFrameLocalWorldMatrixはアニメーションを反映させた状態で取得しないと
		意図した情報を取得することができないので注意
	*/
	// アニメーションの反映
	/*MV1DetachAnim(modelHandle, 0);
	MV1AttachAnim(modelHandle, 0);*/
	//MV1SetAttachAnimTime(modelHandle, 0, animTimer);
	//MATRIX frame_matrix = MV1GetFrameLocalWorldMatrix(modelHandle, 18);
	MATRIX frame_matrix = MV1GetFrameLocalWorldMatrix(GetModelHandle(model.modelKind), 1);

	// 武器用の親行列を変更
	collider.ChangeParentMatrix(frame_matrix);
	// 武器用OBBの位置調整
#define ADJUSTMENT 
#if defined(ADJUSTMENT)

	static Vec3 debug_angle{ InitColliderAngle };
	if (CheckHitKey(KEY_INPUT_J))
	{
		debug_angle.z -= 1.0f;
	}
	else if (CheckHitKey(KEY_INPUT_L))
	{
		debug_angle.z += 1.0f;
	}

	static Vec3 debug_pos{ InitColliderPos };

	float move_speed = 2.0f;
	if (CheckHitKey(KEY_INPUT_A))
	{
		debug_pos.x -= move_speed;
	}
	else if (CheckHitKey(KEY_INPUT_D))
	{
		debug_pos.x += move_speed;
	}

	if (CheckHitKey(KEY_INPUT_W))
	{
		debug_pos.y += move_speed;
	}
	else if (CheckHitKey(KEY_INPUT_S))
	{
		debug_pos.y -= move_speed;
	}

	if (CheckHitKey(KEY_INPUT_Z))
	{
		debug_pos.z -= move_speed;
	}
	else if (CheckHitKey(KEY_INPUT_C))
	{
		debug_pos.z += move_speed;
	}

	collider.ChangePos(debug_pos);
	collider.ChangeAngle(debug_angle);

#endif

}

VECTOR MikuObject::Move01()
{
	float move_speed = 0.5f;
	VECTOR new_pos = model.pos;
	new_pos.x += model.frontVector.x * move_speed;
	new_pos.z += model.frontVector.z * move_speed;
	return new_pos;
}

