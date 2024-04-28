#pragma once


enum class AnimType
{
	Wait,
	Run
};

const int LastAnimationNo = (int)AnimType::Run;
const int MaxAnimationNo = (int)AnimType::Run + 1;

bool GetAnimationNo(AnimType type_, int& out_no);
void ChangeAnimation(int handle_, AnimType next_, AnimType& current_, float& animation_timer_, float& animation_time_);
bool PlayAnimation(float& timer_, float time_);
void SetupDrawAnimation(int handle_, AnimType type_, float anim_timer_);

