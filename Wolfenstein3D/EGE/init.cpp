
#include "easy_engine.h"

#include "map_renderer.h"
#include "player.h"
#include "world_object.h"

using namespace ege;

void EasyEngine::Init()
{
	// Set enigne mode
	//SetMode(EM_DEBUG);

	// Set window size
	EasyWindow::SetWindowSize({ 1000, 700 });

	/* Setup scene */
	
	// Create map object
	EasyObject* map = new EasyObject("Map");
	map->AddScript(new MapRenderer()); // Add map renderer script
	AddObject(map); // Add map object to sceene

	// Create player object
	EasyObject* player = new EasyObject("Player");
	player->AddScript(new Player());
	AddObject(player); // Add player object to scene

	// Create barrel object
	EasyObject* barrel = new EasyObject("Barrel");
	barrel->position = { 1.25f, 7.0f };
	barrel->AddScript(new WorldObject());
	barrel->GetScript<WorldObject>()->texture.LoadPNG("textures/BARTA0.png");
	barrel->GetScript<WorldObject>()->offset = { 0, -150 };
	barrel->GetScript<WorldObject>()->scale = { 0.5f, 0.8f };
	map->AddObject(barrel);
}