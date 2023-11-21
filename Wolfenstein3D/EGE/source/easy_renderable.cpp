
#include "easy_renderable.h"

using namespace ege;

// On start event
void EasyRenderable::OnStart()
{

}

// On update event
void EasyRenderable::OnUpdate(float fDeltaTime)
{
	//EasyUtils::Debug("Kita");
	Render();
}