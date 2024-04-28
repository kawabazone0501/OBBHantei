#include "SceneFactory.h"
#include "TitleScene.h"
#include "GameScene.h"

SceneBase* SceneFactory::Create(SceneBase::Type type_)
{
	SceneBase* new_scene = nullptr;

	switch (type_)
	{
	case SceneBase::Type::Title:
		new_scene = new TitleScene();
		break;
	case SceneBase::Type::Game:
		new_scene = new GameScene();
		break;
	}

	return new_scene;
}
