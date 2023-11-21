#pragma once

#define TEXTURE_COUNT 10

#include "easy_script.h"

#include "easy_texture.h"

using namespace ege;

class Player;

class MapRenderer : public EasyScript
{
private: // Map
	const Dimensions<int> mapSize = { 16, 16 };
	int* map = new int[mapSize.width * mapSize.width]{
		1, 1, 2, 1, 3, 3, 4, 3, 3, 5, 5, 6, 5, 5, 6, 5,
		1, 0, 0, 1, 3, 0, 0, 0, 3, 5, 0, 0, 0, 0, 0, 5,
		2, 0, 0, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6,
		1, 0, 0, 2, 3, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 5,
		1, 0, 0, 1, 4, 0, 0, 0, 3, 6, 0, 0, 0, 0, 0, 5,
		2, 0, 0, 2, 3, 0, 0, 0, 3, 5, 0, 0, 0, 0, 0, 5,
		1, 0, 0, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 6,
		1, 0, 0, 1, 3, 0, 0, 0, 3, 6, 0, 0, 0, 0, 0, 5,
		1, 2, 1, 1, 3, 4, 3, 4, 3, 5, 5, 6, 0, 5, 6, 5,
		7, 7, 8, 7, 7, 8, 7, 7, 8, 7, 7, 8, 0, 8, 7, 7,
		7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
		8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
		7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
		8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
		7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
		7, 7, 8, 7, 7, 8, 7, 7, 8, 7, 7, 8, 7, 7, 8, 7
	};

private: // Player
	Player* player;

private: // Override
	virtual void OnStart(); // On start event
	virtual void OnUpdate(float deltaTime); // On update event

private:
	void RenderBackground();
	void RenderPlayerView();
	void CastRay(int x, float rayAngle);
	void RenderObjects();
	void RenderMinimap();

private: // Textures
	EasyTexture textures[TEXTURE_COUNT];
	
public:
	bool IsWall(Vector2<int> vCoords);
};