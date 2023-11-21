#pragma once

#include <Windows.h>

#include <string>
#include <iostream>

#define PI 3.14159265359f

namespace ege
{
	typedef unsigned int uint;

	template <class T>
	struct Vector2
	{
		T x;
		T y;

		Vector2 operator + (const Vector2<T> vVector)
		{
			return { x + vVector.x, y + vVector.y };
		}

		Vector2 operator * (const float fScalar)
		{
			return {x * fScalar, y * fScalar};
		}
	};

	template <class T = float>
	struct Dimensions
	{
		T width;
		T height;
	};

	struct Color
	{
		byte r; // Red channel value
		byte g; // Green channel value
		byte b; // Blue channel value
		byte a = 255; // Alpha value

		// Predefined colors
		static Color BLACK; // 0 0 0
		static Color WHITE;

		Color operator = (const int nColor)
		{
			r = (byte)(nColor >> 24); // Set red channel value
			g = (byte)(nColor >> 16); // Set green channel value
			b = (byte)(nColor >> 8); // Set blue channel value
			a = (byte)(nColor >> 0); // Set alpha value
			return *this;
		}
	};
	
	//Color Color::BLACK = { 0, 0, 0 }; // 0 0 0
	//Color Color::WHITE = { 255, 255, 255 };

	class EasyUtils
	{
	public:
		static void CreateConsole(std::wstring wsAppName)
		{
			//// Create console
			//AllocConsole();
			//SetConsoleTitleA("EGE Debug"); // Set console title

			//// Get standard io files
			//FILE* fpstdin = stdin;
			//FILE* fpstdout = stdout;
			//FILE* fpstderr = stderr;

			//// Reopen io files
			//freopen_s(&fpstdin, "CONIN$", "r", stdin);
			//freopen_s(&fpstdout, "CONOUT$", "w", stdout);
			//freopen_s(&fpstderr, "CONOUT$", "w", stderr);

			//// Initial console message
			//std::wcout << L" (" + wsAppName + L")" << std::endl << " ";
		}

		static int MIN(int nFirst, int nSecond)
		{
			return (nFirst < nSecond) ? nFirst : nSecond;
		}

		static float MIN(float nFirst, float nSecond)
		{
			return (nFirst < nSecond) ? nFirst : nSecond;
		}

		static int MAX(int nFirst, int nSecond)
		{
			return (nFirst > nSecond) ? nFirst : nSecond;
		}

		static float MAX(float nFirst, float nSecond)
		{
			return (nFirst > nSecond) ? nFirst : nSecond;
		}

		static std::wstring STWS(std::string sString)
		{
			return std::wstring(sString.begin(), sString.end());
		}

		static std::wstring STWS(int nNum)
		{
			std::string sString = std::to_string(nNum);
			return std::wstring(sString.begin(), sString.end());
		}

		static void Debug(std::string sString)
		{
			std::wcout << L"-> " + STWS(sString) << std::endl << " ";
		}

		static void Debug(int nNum)
		{
			std::wcout << L"-> " + STWS(nNum) << std::endl << " ";
		}

		static Color Lerp(Color cBegin, Color cEnd, float t)
		{
			// Clamp t
			if (t < 0.0f) t = 0.0f;
			if (t > 1.0f) t = 1.0f;

			// Lerp colors
			Color cLerp = { cBegin.r, cBegin.g, cBegin.b }; // Create new color
			cLerp.r += (cEnd.r - cBegin.r) * t; // Lerp red channel
			cLerp.g += (cEnd.g - cBegin.g) * t; // Lerp green channel
			cLerp.b += (cEnd.b - cBegin.b) * t; // Lerp blue channel

			return cLerp; // Return lerped color
		}
	};
}
