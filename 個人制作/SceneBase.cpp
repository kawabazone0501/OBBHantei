#include<DxLib.h>
#include "SceneBase.h"

SceneBase::Type SceneBase::Main()
{
	switch (CurrentStep)
	{
	case SceneBase::Step::Init:
		Init();
		break;
	case SceneBase::Step::UpDate:
		UpDate();
		break;
	case SceneBase::Step::Finish:
		return Finish();
		break;
	}

	return GetType();
}
