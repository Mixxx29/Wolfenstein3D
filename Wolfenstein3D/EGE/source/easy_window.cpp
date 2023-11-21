
#include <Windows.h>

#include "easy_window.h"

using namespace ege;

/**************************************** Static **********************************************/

std::atomic<bool>* EasyWindow::m_bRunning = nullptr; // Engine running state

Dimensions<int> EasyWindow::m_dWindowSize; // Window size

void* EasyWindow::m_pvScreenBuffer = nullptr; // Screen buffer pointer

EasyWindow::EasyWindow(std::wstring wsTitle, std::atomic<bool>* bRunning)
{
	m_wsTitle = wsTitle;
	m_bRunning = bRunning;

	// Default window size
	m_dWindowSize = { 960, 640 };

	// Create graphics object
	m_eGraphics = new EasyGraphics(&m_pvScreenBuffer, &m_dWindowSize);
}

// Create window
void EasyWindow::Create()
{
	// Create window class
	WNDCLASS wc;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // Set window icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Set cursor
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; // Set style
	wc.hInstance = GetModuleHandle(NULL); // Set app instance
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpszMenuName = nullptr; // Disable menu
	wc.hbrBackground = nullptr;
	wc.lpszClassName = TEXT("EASY_GRAPHICS_ENGINE");
	wc.lpfnWndProc = WindowEvent; // Set event callback

	// Register new window class
	RegisterClass(&wc);

	// Window styles                                         // Enable Resize
	DWORD dwStyleEx = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;    //      \/
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | /*WS_THICKFRAME |*/ WS_VISIBLE;

	// Set window size
	RECT rWindowRect = { 0, 0, m_dWindowSize.width, m_dWindowSize.height };

	AdjustWindowRectEx(&rWindowRect, dwStyle, FALSE, dwStyleEx); // Adjust window rect

	// Create window
	m_hWND = CreateWindowExA(
		dwStyleEx,
		"EASY_GRAPHICS_ENGINE",
		"Test",
		dwStyle, 
		100, 
		100, 
		rWindowRect.right - rWindowRect.left,
		rWindowRect.bottom - rWindowRect.top,
		NULL,
		NULL,
		wc.hInstance,
		this
	);

	// Get device handler
	m_hDC = GetDC(m_hWND);

	// Create screen buffer
	m_nScreenBufferSize = m_dWindowSize.width * m_dWindowSize.height * sizeof(int);
	if (m_pvScreenBuffer) VirtualFree(m_pvScreenBuffer, 0, MEM_RELEASE);
	m_pvScreenBuffer = VirtualAlloc(0, m_nScreenBufferSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	// Create screen bitmap info
	m_bmInfo.bmiHeader.biSize = sizeof(m_bmInfo.bmiHeader); // Set bitmap info header size
	m_bmInfo.bmiHeader.biWidth = m_dWindowSize.width; // Set width
	m_bmInfo.bmiHeader.biHeight = m_dWindowSize.height; // Set height
	m_bmInfo.bmiHeader.biPlanes = 1;
	m_bmInfo.bmiHeader.biBitCount = 32;
	m_bmInfo.bmiHeader.biCompression = BI_RGB;
}

// Render frame
void EasyWindow::Render()
{
	// Copy screen buffer to screen
	StretchDIBits(
		m_hDC, 
		0, 
		0, 
		m_dWindowSize.width, 
		m_dWindowSize.height, 
		0, 
		0, 
		m_dWindowSize.width, 
		m_dWindowSize.height, 
		m_pvScreenBuffer, 
		&m_bmInfo, 
		DIB_RGB_COLORS, 
		SRCCOPY
	);
}

// Clear screen
void EasyWindow::Clear()
{
	memset(m_pvScreenBuffer, 0, m_nScreenBufferSize); // Reset screen buffer
}

// Updates FPS in title bar
void EasyWindow::FPS(int nFPS)
{
	SetWindowTextW(m_hWND, (m_wsTitle + L"          FPS: " + std::to_wstring(nFPS)).c_str());
}

LRESULT CALLBACK EasyWindow::WindowEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
	case WM_DESTROY:
		*m_bRunning = false; // Stop engine thread
		return 0;

	case WM_SIZE:

		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// Sets window dimensions
void EasyWindow::SetWindowSize(Dimensions<int> dWindowSize)
{
	m_dWindowSize = dWindowSize;
}

// Returns window dimensions
Dimensions<int> EasyWindow::GetWindowSize()
{
	return m_dWindowSize;
}