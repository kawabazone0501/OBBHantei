#include "DxLib.h"
#include "Model.h"
#include <math.h>
#include "Animation.h"
#include "Miku.h"
#include"Enemy.h"
#include "Camera.h"
#include"Shadow.h"
#include "SceneManager.h"


//extern Shadow g_shadow;
extern MikuObject g_Miku;
extern EnemyObject g_Enemy;

//extern int g_ShadowMapHandles[ShadowMapTypeMax];
static int g_ModelHandles[MaxModelKindNum];

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true); // �E�B���h�E���[�h�ɐݒ�
	SetGraphMode(800, 600, 32);	// �E�B���h�E�̃T�C�Y���̐ݒ�

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;				// �G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);	// �`��Ώۂ𗠂̃L�����o�X�Ɏw��

	
	// �J�����ݒ�
	SetCameraNearFar(0.1f, 1000.0f);
	SetCameraPositionAndTargetAndUpVec(
		VGet(0.0f, 10.0f, -30.0f),
		VGet(0.0f, 10.0f, 0.0f),
		VGet(0.0f, 1.0f, 0.0f)
	);

	LoadModel();

	Model Island =
	{
		VGet(0.0f, 0.0f, 0.0f),
		VGet(1.0f, 1.0f, 1.0f),
		VGet(0.0f, 0.0f, 0.0f),
		ModelKind::Island,
	};


	int stage_handle = GetModelHandle(ModelKind::Island);
	MV1SetupCollInfo(
		stage_handle,		// �����蔻���ݒ肷�郂�f���̃n���h��
		-1,					// �ΏۂƂȂ郂�f���̃t���[���ԍ�(-1�͑S��)	
		32,					// X���̋�ԕ�����
		32,					// Y���̋�ԕ�����
		32					// Z���̋�ԕ�����
	);


	SceneManager scene_manager(SceneBase::Type::Title);

	

	//LoadShadow();
	

	

	/*g_Miku.InitializedMiku();
	g_Enemy.InitAnimation();*/

	


	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		scene_manager.Main();

		

		ClearDrawScreen();

		//// Stage�̃V���h�E�}�b�v�̏������݊J�n
		//ShadowMap_DrawSetup(g_ShadowMapHandles[(int)ShadowMapType::Stage]);

		// �V���h�E�}�b�v�փX�e�[�W���f���̕`��
		//MV1DrawModel(stage_handle);

		//// Stage�̃V���h�E�}�b�v�ւ̕`����I��
		//ShadowMap_DrawEnd();

		//// Chara�̃V���h�E�}�b�v�̏������݊J�n
		//ShadowMap_DrawSetup(g_ShadowMapHandles[(int)ShadowMapType::Chara]);

		//// Chara�̃V���h�E�}�b�v�ւ̕`����I��
		//ShadowMap_DrawEnd();

		DrawModel(&Island);
		

		scene_manager.Draw();

		ScreenFlip();
	}
	
	DeleteModel();
	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}