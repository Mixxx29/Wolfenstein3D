#pragma once

#include <vector>

#include "easy_renderable.h"

namespace ege
{
	enum ShapeType
	{
		ST_RECT = 4,
	};

	class EasyShape : public EasyRenderable
	{
	public:
		EasyShape(ShapeType sType, Color cCol);
		virtual void Render();

	private:
		ShapeType m_sType; // Shape type
		Color m_cCol; // Shape color

		std::vector<Vector2<int>> m_vvPoints; // Vector of shape points
	};
}