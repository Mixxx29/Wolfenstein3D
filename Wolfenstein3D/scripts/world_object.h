#pragma once

#include "easy_script.h"

using namespace ege;

class WorldObject : public EasyScript
{
public:
	Vector2<int> offset;
	Vector2<float> scale;
	EasyTexture texture;
	float distance;
	int x;
	Vector2<int> start;
	Vector2<int> end;
	Vector2<float> transform;

private:
	virtual void OnStart();
	virtual void OnUpdate(float deltaTime);
};
