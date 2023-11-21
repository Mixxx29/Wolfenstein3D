#pragma once

#include <Windows.h>
#include <string>
#include <atomic>

#include "utils.h"
#include "easy_graphics.h"

namespace ege
{
	class EasyWindow
	{
	public:
		EasyWindow(std::wstring wsTitle, std::atomic<bool>* bRunning);
		void Create(); // Create window
		void Render(); // Render frame
		void Clear(); // Clear screen
		void FPS(int nFPS); // Updates FPS in title bar

	private:
		static LRESULT CALLBACK WindowEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	public: // Setters
		static void SetWindowSize(Dimensions<int> dWindowSize); // Sets window dimensions

	public: // Getters
		static Dimensions<int> GetWindowSize(); // Returns window dimensions

	private:
		std::wstring m_wsTitle; // Window title

		static std::atomic<bool>* m_bRunning; // Engine running state

		static Dimensions<int> m_dWindowSize; // Window size

		HWND m_hWND; // Window handler
		HDC m_hDC; // Device handler

		int m_nScreenBufferSize; // Screen buffer size
		static void* m_pvScreenBuffer; // Screen buffer pointer
		BITMAPINFO m_bmInfo; // Screen bitmap info

		EasyGraphics* m_eGraphics; // Graphics object
	};
}