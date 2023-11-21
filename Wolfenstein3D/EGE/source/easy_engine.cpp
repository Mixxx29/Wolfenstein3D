
#include "easy_engine.h"

#include <iostream>
#include <thread>
#include <chrono>

using namespace ege;

/**************************************** Static **********************************************/
EasyObject* EasyEngine::m_poScene = nullptr;

EasyEngine::EasyEngine()
{
	m_wsAppName = L"EGE - Demo";

	// Create main window object
	m_eWindow = new EasyWindow(m_wsAppName, &m_bRunning);

	// Create events manager
	m_eEvents = new EasyEvents();

	m_eMode = EM_DEFAULT;

	m_poScene = new EasyObject("Root");
}

void EasyEngine::Run()
{
	// Check engine mode
	switch (m_eMode)
	{
	case EM_DEBUG:
		EasyUtils::CreateConsole(m_wsAppName);
		break;
	}

	// Create main window
	m_eWindow->Create();

	// Set running to true
	m_bRunning = true;

	// Start engine thread
	std::thread t(&EasyEngine::EngineThread, this);

	// Handle events
	MSG msg;
	while (m_bRunning)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
		{
			switch (msg.message)
			{
			// Handle keyboard
			case WM_KEYDOWN:
			case WM_KEYUP:
				m_eEvents->HandleKeyboard(msg.message, msg.wParam, msg.lParam);
				break;

			// Handle mouse
			case WM_LBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_RBUTTONDOWN:
			case WM_RBUTTONUP:
			case WM_MOUSEWHEEL:
			case WM_MOUSEMOVE:
				m_eEvents->HandleMouse(msg.message, msg.wParam, msg.lParam);
				break;

			default:
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				break;
			}
		}
	}

	t.join(); // Wait for thread to finish
}

// Engine thread
void EasyEngine::EngineThread()
{
	// Prepare objects
	m_poScene->OnStart();

	// Time variables
	auto tStart = std::chrono::system_clock::now(); // Frame start time
	auto tEnd = std::chrono::system_clock::now(); // Frame end time
	float fDeltaTime = 0.0f; // Frame duration
	
	// FPS variables
	int nFrames = 0; // Frames counter
	float fFramesTime = 0.0f; // Time passed since counting

	// Engine loop
	while (m_bRunning)
	{
		// Process time
		tEnd = std::chrono::system_clock::now(); // Get current time
		std::chrono::duration<float> dElapsedTime = tEnd - tStart; // Calculate elapsed time
		fDeltaTime = dElapsedTime.count(); // Calculate delta time
		tStart = tEnd; // Set new frame start time

		// Calculate FPS
		nFrames++; // Increment number of frames
		fFramesTime += fDeltaTime; // Add to frames time
		if (fFramesTime >= 1.0f)
		{
			// Update FPS
			m_eWindow->FPS(nFrames);

			// Reset
			nFrames = 0;
			fFramesTime = 0.0f;
		}

		// Process keyboard
		m_eEvents->ProcessKeyboard();

		// Clear screen
		m_eWindow->Clear();

		// Update objects
		m_poScene->OnUpdate(fDeltaTime);

		// Render frame
		m_eWindow->Render();
	}
}

/**************************************** Objects **********************************************/

// Add object to root
void EasyEngine::AddObject(EasyObject* poObject)
{
	m_poScene->AddObject(poObject);
}

// Remove object from root
void EasyEngine::RemoveObject(int index)
{
	m_poScene->RemoveObject(index);
}

// Get object from root
EasyObject* EasyEngine::GetObj(int index)
{
	return m_poScene->GetChild(index);
}

// Find object by name
EasyObject* EasyEngine::Find(std::string sName)
{
	return m_poScene->Find(sName);
}

// Set engine mode
void EasyEngine::SetMode(EngineMode eMode)
{
	m_eMode = eMode;
}

// Set scene object
void EasyEngine::SetScene(EasyObject* poScene)
{
	m_poScene = poScene;
}