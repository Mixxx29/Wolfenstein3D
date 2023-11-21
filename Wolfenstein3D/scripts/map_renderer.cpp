
#include "map_renderer.h"

#include "easy_engine.h"

#include "player.h"
#include "world_object.h"

using namespace ege;

float* zBuffer;

WorldObject* objects[10];

void MapRenderer::OnStart()
{
	// Get player 
	player = EasyEngine::Find("Player")->GetScript<Player>();

	// Load textures
	textures[0].LoadPNG("textures/BRICK_2A.png");
	textures[1].LoadPNG("textures/BRICK_2B.png");
	textures[2].LoadPNG("textures/BRICK_1A.png");
	textures[3].LoadPNG("textures/BRICK_1B.png");
	textures[4].LoadPNG("textures/BRICK_3A.png");
	textures[5].LoadPNG("textures/BRICK_3B.png");
	textures[6].LoadPNG("textures/TECH_0A.png");
	textures[7].LoadPNG("textures/TECH_4E.png");
	textures[8].LoadPNG("textures/FLOOR_1A.png");
	textures[9].LoadPNG("textures/PIPES_2A.png");

	zBuffer = (float*)malloc(EasyWindow::GetWindowSize().width * sizeof(float));

	objects[0] = EasyEngine::Find("Barrel")->GetScript<WorldObject>();
}

void MapRenderer::OnUpdate(float deltaTime)
{
	RenderBackground();
	RenderPlayerView();
	RenderObjects();
	RenderMinimap();
}

void MapRenderer::RenderBackground()
{
	Vector2<float> leftRay = { cosf(player->angle + player->FOV / 2), sinf(player->angle + player->FOV / 2) };
	Vector2<float> rightRay = { cosf(player->angle - player->FOV / 2), sinf(player->angle - player->FOV / 2) };

	float zPos = EasyWindow::GetWindowSize().height / 2.0f;

	// Render floor and ceiling
	for (int y = 0; y < EasyWindow::GetWindowSize().height / 2; y++)
	{
		int p = EasyWindow::GetWindowSize().height / 2 - y;

		float rowDistance = zPos / p * 1.19f;

		Vector2<float> step = { 
			rowDistance * (rightRay.x - leftRay.x) / EasyWindow::GetWindowSize().width,
			rowDistance * (rightRay.y - leftRay.y) / EasyWindow::GetWindowSize().width
		};

		Vector2<float> floor = {
			player->position->x + rowDistance * leftRay.x,
			player->position->y + rowDistance * leftRay.y
		};

		Color c = { 200, 200, 200 };

		for (int x = 0; x < EasyWindow::GetWindowSize().width; x++)
		{
			// Get texture coordinates
			Vector2<int> textureCoords = {
				(int)((floor.x - (int)floor.x) * textures[8].GetSize().width) & (textures[5].GetSize().width - 1),
				(int)((floor.y - (int)floor.y) * textures[8].GetSize().height) & (textures[5].GetSize().height  - 1)
			};

			// Draw floor
			EasyGraphics::DrawPixel({ x, y }, textures[8].GetPixel(textureCoords));

			// Draw ceiling
			EasyGraphics::DrawPixel({ x, EasyWindow::GetWindowSize().height - y - 1 }, textures[9].GetPixel(textureCoords));

			// Increment floor cords
			floor.x += step.x;
			floor.y += step.y;
		}
	}
}

void MapRenderer::RenderPlayerView()
{
	// Get angle between rays
	float deltaRayAngle = player->FOV / EasyWindow::GetWindowSize().width;

	// Get start ray angle
	float rayAngle = player->angle + player->FOV / 2;

	// Cast ray for each screen column
	for (int x = 0; x < EasyWindow::GetWindowSize().width; x++)
	{
		// Cast ray
		CastRay(x, rayAngle - x * deltaRayAngle);
	}
}

void MapRenderer::CastRay(int x, float rayAngle)
{
	// Get ray direction
	Vector2<float> rayDir = { cosf(rayAngle), sinf(rayAngle) };

	// Get tile coordinates
	Vector2<int> tile = { (int)player->position->x, (int)player->position->y };

	// Get initial lenthgs
	Vector2<float> lengths;

	// Get ray step
	Vector2<int> step; 

	if (rayDir.x > 0)
	{
		// Set x step
		step.x = 1;

		//Get intersection x length
		lengths.x = abs(((float)(tile.x + 1) - player->position->x) / rayDir.x);
	}
	else
	{
		// Set x step
		step.x = -1;

		//Get intersection x length
		lengths.x = abs((player->position->x - (float)tile.x) / rayDir.x);

	}

	if (rayDir.y > 0)
	{
		// Set x step
		step.y = 1;

		//Get intersection y length
		lengths.y = abs((((float)(tile.y + 1)) - player->position->y) / rayDir.y);

	}
	else
	{
		// Set x step
		step.y = -1;

		//Get intersection y length
		lengths.y = abs((player->position->y - (float)tile.y) / rayDir.y);
	}  

	bool hit = false;

	Vector2<float> intersection;

	float distance = 0.0f;
	float offset = 0.0f;

	// Start
	while (!hit)
	{
		if (lengths.x < lengths.y)
		{
			tile.x += step.x;
			if (map[tile.y * mapSize.width + tile.x] != 0)
			{
				hit = true;
				distance = lengths.x;
				offset = (distance * rayDir.y) + player->position->y;
				offset -= (int)offset;
			}

			lengths.x += abs(1.0f / rayDir.x);
		}
		else
		{
			tile.y += step.y;
			if (map[tile.y * mapSize.width + tile.x] != 0)
			{
				hit = true;
				distance = lengths.y;
				offset = (distance * rayDir.x) + player->position->x;
				offset -= (int)offset;
			}

			lengths.y += abs(1.0f / rayDir.y);
		}
	}

	float k = cosf(rayAngle - player->angle);
	distance *= k;

	zBuffer[x] = distance;

	// Render part of wall
	int windowHeight = EasyWindow::GetWindowSize().height;
	if (distance <= 0) distance = 0.01f;
	int lineHeight = windowHeight / distance;
	int tileIndex = map[tile.y * mapSize.width + tile.x] - 1;
	for (int y = 0; y < lineHeight; y++)
	{
		Color c = textures[tileIndex].GetPixel({ 
			(int)(offset * textures[tileIndex].GetSize().width), 
			(int)((float)y / lineHeight * textures[tileIndex].GetSize().height)
		});
		EasyGraphics::DrawPixel({ x, y + (windowHeight - lineHeight) / 2 }, c);
	}
}

void MapRenderer::RenderObjects()
{
	for (int i = 0; i < 9; i++)
	{
		if (objects[i] == nullptr) break;
		int max = i;

		for (int j = i + 1; j < 10; j++)
		{
			if (objects[j] == nullptr) break;

			if (objects[j]->distance > objects[max]->distance)
			{
				max = j;
			}
		}

		if (max == i) continue;

		WorldObject* temp = objects[i];
		objects[i] = objects[max];
		objects[max] = temp;
	}

	for (int i = 0; i < 10; i++)
	{
		if (objects[i] == nullptr) break;

		for (int x = objects[i]->start.x; x < objects[i]->end.x; x++)
		{
			int texX = int(256 * (x - (objects[i]->x - objects[i]->size->width / 2)) * objects[i]->texture.GetSize().width / objects[i]->size->width) / 256;
			if (objects[i]->transform.y > 0 && x > 0 && x < EasyWindow::GetWindowSize().width && objects[i]->transform.y < zBuffer[x])
			{
				for (int y = objects[i]->start.y; y < objects[i]->end.y; y++)
				{
					int texY = (y - objects[i]->offset.y / objects[i]->transform.y) * 256 - (EasyWindow::GetWindowSize().height - objects[i]->size->height) * 128;
					texY = (texY * objects[i]->texture.GetSize().height) / objects[i]->size->height / 256;

					EasyGraphics::DrawPixel(
						{ x, y },
						objects[i]->texture.GetPixel({ texX, texY })	
					);
				}
			}
		}
	}
}

	// Render minimap to screen
void MapRenderer::RenderMinimap()
{
	int tileScale = 10;
	int height = EasyWindow::GetWindowSize().height;
	for (int x = 0; x < mapSize.width; x++)
	{
		for (int y = 0; y < mapSize.height; y++)
		{
			Color c;
			switch (map[y * mapSize.width + x])
			{
			case 0: c = { 255, 255, 255 }; break;
			default:
				c = { 50, 50, 50 };
				break;
			}

			EasyGraphics::FillRect({ 5 + x * tileScale, height - mapSize.height * tileScale + y * tileScale - 5 }, { tileScale, tileScale }, c);
						
		}
	}

	// Render player
	EasyGraphics::FillRect(
		{ (int)(player->position->x * tileScale) + 5, height - mapSize.height * tileScale - 5 + (int)(player->position->y * tileScale) },
		{ 5, 5 },
		{ 255, 0, 0}
	);

	// Render player direction
	EasyGraphics::DrawLine(
		{ (int)(player->position->x * tileScale + 7.5f), (int)(height - mapSize.height * tileScale - 2.5f + (int)(player->position->y * tileScale)) },
		{ (int)((player->position->x * tileScale + 7.5f) + (cosf(player->angle) * 7.5f)), (int)((height - mapSize.height * tileScale - 2.5f + (int)(player->position->y * tileScale)) + (sinf(player->angle)) * 7.5f) },
		{ 255, 0, 0}
	);
}

bool MapRenderer::IsWall(Vector2<int> vCoords)
{
	return map[vCoords.y * mapSize.width + vCoords.x] != 0;
}