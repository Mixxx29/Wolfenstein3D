
#include "easy_graphics.h"

using namespace ege;

/************************************* Static *************************************/

void** EasyGraphics::m_ppvScreenBuffer = nullptr; // Pointer to screen buffer
Dimensions<int>* EasyGraphics::m_pdWindowSize = nullptr; // Pointer to window dimensions

EasyGraphics::EasyGraphics(void** ppvScreenBuffer, Dimensions<int>* pdWindowSize)
{
	m_ppvScreenBuffer = ppvScreenBuffer; // Set screen buffer pointer
	m_pdWindowSize = pdWindowSize; // Set window dimensions pointer
}

/********************************** Drawing logic **********************************/

// Draws pixel to screen
void EasyGraphics::DrawPixel(Vector2<int> vPos, Color cCol)
{
	// Check if pixel is out of screen
	if (vPos.x < 0 || vPos.x >= m_pdWindowSize->width) return;
	if (vPos.y < 0 || vPos.y >= m_pdWindowSize->height) return;
	
	// Check if color alpha value is 0%
	if (cCol.a == 0) return;

	// Get screen buffer
	int* pnScreenBuffer = (int*)(*m_ppvScreenBuffer);

	// Get pixel index
	int nIndex = vPos.y * m_pdWindowSize->width + vPos.x;

	// Check if color alpha value is 100%
	if (cCol.a == 255)
	{
		// Set new color
		pnScreenBuffer[nIndex] = 0; // Reset color
		pnScreenBuffer[nIndex] += cCol.r << 16; // Set red channel
		pnScreenBuffer[nIndex] += cCol.g << 8; // Set green channel
		pnScreenBuffer[nIndex] += cCol.b; // Set blue channel
		return;
	}

	// Get pixel RGB values
	byte r = (byte)(pnScreenBuffer[nIndex] >> 16); // Get pixel red channel value
	byte g = (byte)(pnScreenBuffer[nIndex] >> 8); // Get pixel green channel value
	byte b = (byte)(pnScreenBuffer[nIndex]); // Get pixel blue channel value

	// Calculate new color
	r = ((cCol.r * cCol.a) + (r * ((byte)255 - cCol.a))) / (byte)255; // Calculate red channel value
	g = ((cCol.g * cCol.a) + (g * ((byte)255 - cCol.a))) / (byte)255; // Calculate green channel value
	b = ((cCol.b * cCol.a) + (b * ((byte)255 - cCol.a))) / (byte)255; // Calculate blue channel value

	// Set new color
	pnScreenBuffer[nIndex] = 0; // Reset color
	pnScreenBuffer[nIndex] += r << 16; // Set red channel
	pnScreenBuffer[nIndex] += g << 8; // Set green channel
	pnScreenBuffer[nIndex] += b; // Set blue channel
}

void ege::EasyGraphics::DrawLine(Vector2<int> vFirst, Vector2<int> vSecond, Color cCol)
{
	int dx = abs(vSecond.x - vFirst.x);
	int sx = vFirst.x < vSecond.x ? 1 : -1;
	int dy = -abs(vSecond.y - vFirst.y);
	int sy = vFirst.y < vSecond.y ? 1 : -1;
	int error = dx + dy;

	if (dx == 0) // Line is vertical
	{
		int nStart = EasyUtils::MIN(vFirst.y, vSecond.y);
		int nEnd = EasyUtils::MAX(vFirst.y, vSecond.y);
		for (int y = nStart; y <= nEnd; y++)
		{
			DrawPixel({ vFirst.x, y }, cCol);
		}
		return;
	}

	if (dy == 0) // Line is horizontal
	{
		int nStart = EasyUtils::MIN(vFirst.x, vSecond.x);
		int nEnd = EasyUtils::MAX(vFirst.x, vSecond.x);
		for (int x = nStart; x <= nEnd; x++)
		{
			DrawPixel({ x, vFirst.y }, cCol);
		}
		return;
	}

	while (true)
	{
		DrawPixel({ vFirst.x, vFirst.y }, cCol);
		if (vFirst.x == vSecond.x && vFirst.y == vSecond.y) break;
		int error2 = 2 * error;
		if (error2 >= dy)
		{
			if (vFirst.x == vSecond.x) break;
			error += dy;
			vFirst.x += sx;
		}

		if (error2 <= dx)
		{
			if (vFirst.y == vSecond.y) break;
			error += dx;
			vFirst.y += sy;
		}
	}
}

// Draws filled rectangle to screen
void EasyGraphics::FillRect(Vector2<int> vPos, Dimensions<int> dSize, Color cCol)
{
	for (int x = vPos.x; x < vPos.x + dSize.width; x++)
	{
		for (int y = vPos.y; y < vPos.y + dSize.height; y++)
		{
			DrawPixel({x, y}, cCol);
		}
	}
}

// Draw texture to screen
void EasyGraphics::DrawTexture(Vector2<int> vPos, EasyTexture eTexture)
{
	for (int x = 0; x < eTexture.GetSize().width; x++)
	{
		for (int y = 0; y < eTexture.GetSize().height; y++)
		{
			DrawPixel({ vPos.x + x, vPos.y + y }, eTexture.GetPixel({ x, y }));
		}
	}
}