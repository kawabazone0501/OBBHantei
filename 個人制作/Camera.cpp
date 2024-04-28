#include <math.h>
#include <DxLib.h>
#include "Miku.h"

static float g_RevolutionCameraAngle = 0.0f;

static float g_ElevationCameraAngle = 90.0f;

extern MikuObject g_Miku;

void UpdateTPSCamera()
{
	VECTOR target_pos = g_Miku.GetMikuPos();

	VECTOR target_front_vec = g_Miku.GetMikuFrontVector();

	VECTOR inverse_vec = VScale(target_front_vec, -1.0f);

	float camera_distance = 20.0f;
	inverse_vec = VScale(inverse_vec, camera_distance);

	VECTOR new_pos = VAdd(target_pos, inverse_vec);
	new_pos.y += 10.0f;
	target_pos.y += 5.0f;

	SetCameraPositionAndTargetAndUpVec(
		new_pos,
		target_pos,
		VGet(0.0f, 1.0f, 0.0f)
	);
}

void UpdateCamera()
{
	UpdateTPSCamera();
}