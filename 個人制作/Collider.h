#pragma once

#include "Common.h"
#include <vector>
#include <utility>

/*
	OBB��8�̒��_���W�ŋ^���I�Ȓ����̂����Ή�����

	�P�D�ӂ̒����P�̗����̂����
	�Q�D�ϊ��s������
	�R�D�P�̗����̂̒��_ * �ϊ��s��Œ����̂̒��_���W�����߂�
*/
// OBB�\����
struct OBBCollider
{
public:
	static constexpr int MaxVertex = 8;

	OBBCollider(Vec3 pos_, Vec3 size_, Vec3 angle_);

	//�ύX�֐�
	void ChangePos(Vec3& pos_);
	void ChangeAngle(Vec3& angle_);
	void ChangeSize(Vec3& size_);
	void ChangeParentMatrix(MATRIX& parent_mat);

	//OBB���烍�[�J�������擾����
	void GetAxis(Vec3& x_axis, Vec3& y_axis_, Vec3& z_axis_);
	void GetAxis(Axis& axis_);

#if defined(DEBUG)
	//���C���[�t���[���ŕ`��
	void Draw();
#endif

public:
	//���݂̒��_���W
	Vec3 currentVertices[MaxVertex]{};

private:
	//�s��X�V
	void UpDate();

	MATRIX translateMat{ MGetIdent() };	// ���s�ړ��s��
	MATRIX rotateMat{ MGetIdent() };	// ��]�s��
	MATRIX scaleMat{ MGetIdent() };		// �g�k�s��		
	MATRIX transformMat{ MGetIdent() };	// �ϊ��s��
	MATRIX parentMat{ MGetIdent() };	// �e�̕ϊ��s��
};