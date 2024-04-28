#pragma once
class SceneBase
{
public:
	enum class Step
	{
		Init,
		UpDate,
		Finish
	};

	enum class Type
	{
		Title,
		Game
	};

public:
	SceneBase():
		CurrentStep(Step::Init)
	{
	}

	virtual ~SceneBase()
	{
	}

	Type Main();
	virtual void Draw() = 0;
	virtual Type GetType() = 0;

protected:
	virtual void Init() = 0;
	virtual void UpDate() = 0;
	virtual Type Finish() = 0;
protected:
	Step CurrentStep;
};

