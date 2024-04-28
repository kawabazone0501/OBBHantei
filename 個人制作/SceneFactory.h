#pragma once

#include"SceneBase.h"

class SceneFactory
{
public:
	static SceneBase* Create(SceneBase::Type type_);
};

