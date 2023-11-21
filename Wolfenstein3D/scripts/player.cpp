
#include "player.h"

#include "easy_engine.h"

#include "map_renderer.h"

void Player::OnStart()
{
	// Get map renderer
	mapRenderer = EasyEngine::Find("Map")->GetScript<MapRenderer>();

	// Set player position
	SetPosition({ 2.0f, 1.25f });
}

void Player::OnUpdate(float deltaTime)
{
	if (EasyEvents::GetKeyHeld('W'))
	{
		position->x += cosf(angle) * speed * deltaTime;
		position->y += sinf(angle) * speed * deltaTime;

		if (mapRenderer->IsWall({ (int)position->x, (int)position->y }))
		{
			position->x -= cosf(angle) * speed * deltaTime;
			position->y -= sinf(angle) * speed * deltaTime;
		}
	}

	if (EasyEvents::GetKeyHeld('S'))
	{
		position->x -= cosf(angle) * speed * deltaTime;
		position->y -= sinf(angle) * speed * deltaTime;

		if (mapRenderer->IsWall({ (int)position->x, (int)position->y }))
		{
			position->x += cosf(angle) * speed * deltaTime;
			position->y += sinf(angle) * speed * deltaTime;
		}
	}

	if (EasyEvents::GetKeyHeld('D'))
	{
		angle -= rotationSpeed * deltaTime;
	}

	if (EasyEvents::GetKeyHeld('A'))
	{
		angle += rotationSpeed * deltaTime;
	}
}