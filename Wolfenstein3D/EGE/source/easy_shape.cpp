
#include "easy_shape.h"
#include "easy_graphics.h"

using namespace ege;

EasyShape::EasyShape(ShapeType sType, Color cCol)
{
	m_sType = sType;
	m_cCol = cCol;
}

void EasyShape::Render()
{
	switch (m_sType)
	{
	case ST_RECT:
		EasyGraphics::FillRect(
			{(int)GetPosition().x, (int)GetPosition().y},
			{(int)GetSize().width, (int)GetSize().height},
			m_cCol
		);
		break;
	}
}