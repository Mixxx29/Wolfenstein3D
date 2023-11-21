#pragma once

#include "utils.h"

namespace ege
{
	class EasyTexture
	{
	public:
		EasyTexture();
		void LoadPNG(std::string sPath); // Load texture from png image

	public:
		Dimensions<int> GetSize(); // Get texture dimensions
		Color GetPixel(Vector2<int> vCoords); // Get pixel at coordinates

	private:
		Color* m_cPixels; // Pixels data
		Dimensions<int> m_dSize; // Texture dimensions
	};
}