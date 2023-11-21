
#include "easy_texture.h"

#include "stb_image.h"

extern "C" {
	#define STB_IMAGE_IMPLEMENTATION
	#include "stb_image.h"
}

using namespace ege;

EasyTexture::EasyTexture()
{

}

// Load texture from png image
void EasyTexture::LoadPNG(std::string sPath)
{
	// Load image data
	int n;
	byte* data = stbi_load(
		sPath.c_str(), &m_dSize.width, &m_dSize.height, &n, 0
	);

	// Create pixels array
	m_cPixels = new Color[m_dSize.width * m_dSize.height];

	// Load pixels
	for (int x = 0; x < m_dSize.width; x++)
	{
		for (int y = 0; y < m_dSize.height; y++)
		{
			int index = y * m_dSize.width + x;
			int invertedIndex = (m_dSize.height - y - 1) * m_dSize.width + x;
			m_cPixels[index].r = data[invertedIndex * n + 0]; // Get red channel value
			m_cPixels[index].g = data[invertedIndex * n + 1]; // Get green channel value
			m_cPixels[index].b = data[invertedIndex * n + 2]; // Get blue channel value
			if (n == 4) m_cPixels[index].a = data[invertedIndex * n + 3]; // Get alpha value
		}
	}

	// Release data
	stbi_image_free(data);
}

// Get texture dimensions
Dimensions<int> EasyTexture::GetSize()
{
	return m_dSize;
}

// Get pixel at coordinates
Color EasyTexture::GetPixel(Vector2<int> vCoords)
{
	return m_cPixels[vCoords.y * m_dSize.width + vCoords.x];
}