#pragma once

#include "utils.h"
#include "easy_texture.h"

namespace ege
{
	// EasyGraphicsEngine graphics class
	class EasyGraphics
	{
	public:
		EasyGraphics(void** ppvScreenBuffer, Dimensions<int>* pdWindowSize);

	public: // Drawing logic
		static void DrawPixel(Vector2<int> vPos, Color cCol = { 255, 255, 255 }); // Draws pixel to screen
		static void DrawLine(Vector2<int> vFirst, Vector2<int> vSecond, Color cCol = { 255, 255, 255 }); // Draw line on screen
		static void FillRect(Vector2<int> vPos, Dimensions<int> dSize, Color cCol = { 255, 255, 255 }); // Draws filled rectangle to screen
		static void DrawTexture(Vector2<int> vPos, EasyTexture eTexture); // Draw texture to screen

	private:
		static void** m_ppvScreenBuffer; // Pointer to pixel array
		static Dimensions<int>* m_pdWindowSize; // Pointer to window dimensions
	};
}
