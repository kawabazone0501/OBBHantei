#include "SceneManager.h"

void SceneManager::Main()
{
	SceneBase::Type before = CurrentScene->GetType();
	SceneBase::Type after = CurrentScene->Main();

	if (before != after)
	{
		delete(CurrentScene);

		CurrentScene = SceneFactory::Create(after);
	}

}

void SceneManager::Draw()
{
	CurrentScene->Draw();
}
