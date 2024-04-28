#pragma once

#include"SceneBase.h"
#include"SceneFactory.h"

class SceneManager
{
public:
	SceneManager(SceneBase::Type first_type_) :
		CurrentScene(nullptr)
	{
		CurrentScene = SceneFactory::Create(first_type_);
	}

	void Main();
	void Draw();

private:
	SceneBase* CurrentScene;
};

