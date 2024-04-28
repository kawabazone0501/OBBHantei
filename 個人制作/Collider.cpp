#include"DxLib.h"
#include "Collider.h"

OBBCollider::OBBCollider(Vec3 pos_, Vec3 size_, Vec3 angle_)
{
	translateMat = MGetIdent();
	CreateTranslationMatrix(&translateMat, pos_.x, pos_.y, pos_.z);

	scaleMat = MGetIdent();
	CreateScalingMatrix(&scaleMat, size_.x, size_.y, size_.z);

	VECTOR angle_rad = VScale(angle_.ToVECTOR(), DX_PI / 180.0f);
	rotateMat = MGetIdent();
	CreateRotationXYZMatrix(&rotateMat, angle_rad.x, angle_rad.y, angle_rad.z);

	UpDate();
}

void OBBCollider::ChangePos(Vec3& pos_)
{
	translateMat = MGetIdent();
	CreateTranslationMatrix(&translateMat, pos_.x, pos_.y, pos_.z);

	UpDate();
}

void OBBCollider::ChangeAngle(Vec3& angle_)
{
	VECTOR angle_rad = VScale(angle_.ToVECTOR(), DX_PI / 180.0f);
	rotateMat = MGetIdent();
	CreateRotationXYZMatrix(&rotateMat, angle_rad.x, angle_rad.y, angle_rad.z);

	UpDate();
}

void OBBCollider::ChangeSize(Vec3& size_)
{
	scaleMat = MGetIdent();
	CreateScalingMatrix(&scaleMat, size_.x, size_.y, size_.z);

	UpDate();
}

void OBBCollider::ChangeParentMatrix(MATRIX& parent_mat)
{
	parentMat = parent_mat;

	UpDate();
}

void OBBCollider::GetAxis(Axis& axis_)
{
	GetAxis(axis_.x, axis_.y, axis_.z);
}

//OBB���烍�[�J�������擾����
void OBBCollider::GetAxis(Vec3& x_axis_, Vec3& y_axis_, Vec3& z_axis_)
{
	MATRIX mat = rotateMat;
	//�s�x�N�g���Ōv�Z����Ă���̂ŁA�s��̍s���e���̐���
	x_axis_ = Vec3(mat.m[0][0], mat.m[0][1], mat.m[0][2]);
	y_axis_ = Vec3(mat.m[1][0], mat.m[1][1], mat.m[1][2]);
	z_axis_ = Vec3(mat.m[2][0], mat.m[2][1], mat.m[2][2]);
}

void OBBCollider::UpDate()
{
	const static Vec3 vertices[] =
	{
		{ -0.5f, 0.5f, -0.5f },		// x�F�� y�F�� z�F��O
		{ 0.5f, 0.5f, -0.5f },		// x�F�E y�F�� z�F��O
		{ 0.5f, -0.5f, -0.5f },		// x�F�E y�F�� z�F��O
		{ -0.5f, -0.5f, -0.5f },	// x�F�� y�F�� z�F��O

		{ -0.5f, 0.5f, 0.5f },		// x�F�� y�F�� z�F��
		{ 0.5f, 0.5f, 0.5f },		// x�F�E y�F�� z�F��
		{ 0.5f, -0.5f ,0.5f },		// x�F�E y�F�� z�F��
		{ -0.5f ,-0.5f, 0.5f },		// x�F�� y�F�� z�F��
	};

	transformMat = MGetIdent();
	// ���΍s����쐬
	transformMat = MMult(transformMat, scaleMat);
	transformMat = MMult(transformMat, rotateMat);
	transformMat = MMult(transformMat, translateMat);
	// ���΍s�� * �e�̍s��
	transformMat = MMult(transformMat, parentMat);

	for (int i = 0; i < MaxVertex; i++)
	{
		// �����̂�8���_���X�V����
		currentVertices[i] = VTransform(vertices[i].ToVECTOR(), transformMat);
	}
}

#if defined (DEBUG)

void OBBCollider::Draw()
{
	std::vector<std::pair<Vec3, Vec3>>line_list =
	{
		{currentVertices[0],currentVertices[1]},
		{currentVertices[1],currentVertices[2]},
		{currentVertices[2],currentVertices[3]},
		{currentVertices[3],currentVertices[0]},

		{currentVertices[4],currentVertices[5]},
		{currentVertices[5],currentVertices[6]},
		{currentVertices[6],currentVertices[7]},
		{currentVertices[7],currentVertices[4]},

		{currentVertices[0],currentVertices[4]},
		{currentVertices[1],currentVertices[5]},
		{currentVertices[2],currentVertices[6]},
		{currentVertices[3],currentVertices[7]},
	};

	unsigned int color = GetColor(255, 255, 255);
	for (const auto& pair : line_list)
	{
		DrawLine3D(pair.first.ToVECTOR(), pair.second.ToVECTOR(), color);
	}
}


#endif