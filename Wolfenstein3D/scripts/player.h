#pragma once

#include "easy_script.h"

class MapRenderer;

class Player : public ege::EasyScript
{
public:
	float angle = PI / 2;
	float FOV = PI / 180 * 66.6f; // 66.6 degrees
	float speed = 3.0f;
	float rotationSpeed = 2.5f;

	MapRenderer* mapRenderer;

private:
	virtual void OnStart();
	virtual void OnUpdate(float deltaTime);
};