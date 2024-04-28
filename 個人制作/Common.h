#pragma once

#include"DxLib.h"
#include <math.h>

// �f�o�b�O�p�̃}�N��
#define DEBUG

//3�����x�N�g��
struct Vec3
{
	Vec3()
	{
	}

	Vec3(float x_, float y_, float z_) :
		x{ x_ },
		y{ y_ },
		z{ z_ }
	{
	}

	Vec3(const VECTOR& vec_)
	{
		x = vec_.x;
		y = vec_.y;
		z = vec_.z;
	}

	Vec3 operator + (const Vec3& vec_)
	{
		Vec3 vec;
		vec.x = this->x + vec_.x;
		vec.y = this->y + vec_.y;
		vec.z = this->z + vec_.z;

		return vec;
	}

	Vec3 operator - (const Vec3& vec_)
	{
		Vec3 vec;
		vec.x = this->x + vec_.x;
		vec.y = this->y + vec_.y;
		vec.z = this->z + vec_.z;

		return vec;
	}

	float Norm() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	Vec3 Normalized() const
	{
		float norm = Norm();
		if (norm == 0.0f)
		{
			return Vec3();
		}
		return Vec3(x / norm, y / norm, z / norm);
	}

	VECTOR ToVECTOR() const
	{
		return VGet(x, y, z);
	}

	float x{ 0.0f };
	float y{ 0.0f };
	float z{ 0.0f };
};

// 3�������x�N�g��
struct Axis
{
	Axis()
	{
	}

	Axis(Vec3 x_, Vec3 y_, Vec3 z_) :
		x{ x_ },
		y{ y_ },
		z{ z_ }
	{
	}

	void ToArray(Vec3 list_[3])
	{
		list_[0] = x;
		list_[1] = y;
		list_[2] = z;
	}

	Vec3 x{};
	Vec3 y{};
	Vec3 z{};
};
enum TexturKind
{
	TexturKindTitle,		//�^�C�g��
	TexturKindMax,			//�e�N�X�`���̎�ނ̍ő�
};

enum SceneType
{
	SceneTypeGame,	//GameScene
	SceneTypeTitle,//TitleScene
};

enum SceneStep
{
	SceneStepInit,		//������
	SceneStepRun,		//���s
	SceneStepFinish		//�I��
};
