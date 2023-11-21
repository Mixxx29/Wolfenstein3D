
#include "world_object.h"

#include "easy_engine.h"

#include "player.h"

Player* player;

void WorldObject::OnStart()
{
	player = EasyEngine::Find("Player")->GetScript<Player>();
}

void WorldObject::OnUpdate(float deltaTime)
{
	Vector2<float> toPlayer = {
		position->x - player->position->x,
		position->y - player->position->y
	};

	Vector2<float> playerDir = {
		cosf(player->angle), sinf(player->angle)
	};

	Vector2<float> camDir = {
		cosf(player->angle - 90 * PI / 180), 
		sinf(player->angle - 90 * PI / 180), 
	};

	distance = toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y;

	float invDet = 1.0f / (camDir.x * playerDir.y - playerDir.x * camDir.y);

	transform = {
		invDet * (playerDir.y * toPlayer.x - playerDir.x * toPlayer.y),
		invDet * (-camDir.y * toPlayer.x + camDir.x * toPlayer.y)
	};

	x = int(EasyWindow::GetWindowSize().width / 2 * (1 + transform.x / transform.y));

	size->height = abs(int(EasyWindow::GetWindowSize().height / transform.y)) * scale.y;
	size->width = abs(int(EasyWindow::GetWindowSize().height / transform.y)) * scale.x;

	start.y = EasyWindow::GetWindowSize().height / 2 - size->height / 2 + offset.y / transform.y;
	if (start.y < 0) start.y = 0;
	end.y = EasyWindow::GetWindowSize().height / 2 + size->height / 2 + offset.y / transform.y;
	if (end.y >= EasyWindow::GetWindowSize().height) end.y = EasyWindow::GetWindowSize().height - 1;

	start.x = x - size->width / 2;
	if (start.x < 0) start.x = 0;
	end.x = x + size->width / 2;
	if (end.x >= EasyWindow::GetWindowSize().width) end.x = EasyWindow::GetWindowSize().width - 1;
}