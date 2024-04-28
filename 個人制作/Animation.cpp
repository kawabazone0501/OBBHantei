#include <math.h>
#include <DxLib.h>
#include "Animation.h"


extern int g_ConverList[]
{
	0,//Wait
	1,//Run
};

bool IsOutOfRange(int min, int max, int value)
{
	if (value<min ||
		value>max)
	{
		return true;
	}

	return false;
}

bool GetAnimationNo(AnimType type_, int& out_no)
{
	if (IsOutOfRange(0, LastAnimationNo, (int)type_) == true)
	{
		return false;
	}
	out_no = g_ConverList[(int)type_];
	return true;
}

void ChangeAnimation(int handle_, AnimType next_, AnimType& current_, float& animation_timer_, float& animation_time_)
{
	int anim_id = -1;
	if (GetAnimationNo(next_, anim_id) == false)
	{
		return;
	}
	animation_time_ = MV1GetAnimTotalTime(handle_, anim_id);
	animation_timer_ = 0.0f;
	current_ = next_;
}

bool PlayAnimation(float& timer_, float time_)
{
	timer_ += 1.0f;

	if (timer_ >= time_)
	{
		return true;
	}
	return false;
}

void SetupDrawAnimation(int handle_, AnimType type_, float anim_timer_)
{
	int anim_id = -1;
	if (GetAnimationNo(type_, anim_id) == false)
	{
		return;
	}

	MV1DetachAnim(handle_, 0);
	MV1AttachAnim(handle_, anim_id);
	MV1SetAttachAnimTime(handle_, 0, anim_timer_);
}