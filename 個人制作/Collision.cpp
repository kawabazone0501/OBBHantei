#include <DxLib.h>
#include "Common.h"
#include "Collider.h"
#include "Collision.h"

//��������������
bool IsFindOBBSparationAxis(const Vec3& axis_, Vec3 vertices_01_[8], Vec3 vertices_02_[8])
{
	Vec3* vertices_list[2]
	{
		vertices_01_,
		vertices_02_
	};

	struct Range
	{
		float min{ 1000000.0f };
		float max{ -1000000.0f };
	};

	Range ranges[2];

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Vec3 vertex = vertices_list[i][j];
			float dot = axis_.x * vertex.x + axis_.y * vertex.y + axis_.z * vertex.z;

			if (ranges[i].min > dot)
			{
				ranges[i].min = dot;
			}
			if (ranges[i].max < dot)
			{
				ranges[i].max = dot;
			}
		}
	}

	//�������Ă���̂ŕ������ł͂Ȃ�
	if (ranges[0].min <= ranges[1].max &&
		ranges[1].min <= ranges[0].max)
	{
		return false;
	}

	return true;
}

// OBB�̃��[�J������SAT���s��
bool CheckOBBLocalAxisSAT(Axis axes_list_[2], Vec3 vertices_list_[2][8])
{
	for (int i = 0; i < 2; i++)
	{
		Vec3 axes[3];
		axes_list_[i].ToArray(axes);

		for (int j = 0; j < 3; j++)
		{
			if (IsFindOBBSparationAxis(axes[j].Normalized(), vertices_list_[0], vertices_list_[1]) == true)
			{
				//����������������
				return true;
			}
		}
	}
	return false;
}

//OBB�̃��[�J�������m�ŊO�ς��s���A���̃x�N�g����SAT���s��
bool CheckOBBCrossVecSAT(Axis axes_[2], Vec3 vertices_list_[2][8])
{
	for (int i = 0; i < 3; i++)
	{
		Vec3 collider_a_axes[3]{};
		axes_[0].ToArray(collider_a_axes);

		for (int j = 0; j < 3; j++)
		{
			Vec3 collider_b_axes[3]{};
			axes_[1].ToArray(collider_b_axes);
			Vec3 cross{ VCross(collider_a_axes[i].ToVECTOR(),collider_b_axes[j].ToVECTOR()) };

			if (IsFindOBBSparationAxis(cross.Normalized(), vertices_list_[0], vertices_list_[1]) == true)
			{
				//����������������
				return true;
			}
		}
	}
	return false;
}

// OBB���m�̔���
bool IsCollingOBBAndOBB(OBBCollider& collider_01_, OBBCollider& collider_02_)
{
	Vec3 vertices_list[2][8]{};
	for (int i = 0; i < 8; i++)
	{
		vertices_list[0][i] = collider_01_.currentVertices[i];
		vertices_list[1][i] = collider_02_.currentVertices[i];
	}

	Axis axes[2]{};
	collider_01_.GetAxis(axes[0]);
	collider_02_.GetAxis(axes[1]);

	//OBB�̃��[�J������SAT���s��
	if (CheckOBBLocalAxisSAT(axes, vertices_list) == true)
	{
		//�����������������̂œ������ĂȂ�
		return false;
	}

	if (CheckOBBCrossVecSAT(axes, vertices_list) == true)
	{
		// �����������������̂œ������Ă��Ȃ�
		return false;
	}

	return true;
}