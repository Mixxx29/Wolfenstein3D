#pragma once

#include "easy_script.h"

namespace ege
{
	enum RenderableType
	{
		RT_SHAPE,
		RT_SPRITE
	};

	class EasyRenderable : public EasyScript
	{
	public: // Override
		virtual void OnStart(); // On start event
		virtual void OnUpdate(float fDeltaTime); // On update event

	public: // Abstract
		virtual void Render() = 0;
	};
}
