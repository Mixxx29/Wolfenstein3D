#pragma once

#include <atomic>

#include "easy_window.h"
#include "easy_events.h"
#include "easy_object.h"

namespace ege
{
	enum EngineMode
	{
		EM_DEFAULT,
		EM_DEBUG
	};

	class EasyEngine
	{
	public:
		EasyEngine();
		void Init(); // Initialize engine data
		void Run(); // Run engine
		void EngineThread(); // Engine thread

	public: // Objects
		void AddObject(EasyObject* poObject); // Add object to root
		void RemoveObject(int index); // Remove object from root
		EasyObject* GetObj(int index); // Get object from root
		static EasyObject* Find(std::string sName); // Find object by name

	public:

	public: // Setters
		void SetMode(EngineMode eMode); // Set engine mode
		void SetScene(EasyObject* poScene); // Set scene object

	private:
		std::wstring m_wsAppName;
		
		EasyWindow* m_eWindow; // Main window
		EasyEvents* m_eEvents; // Events manager

		std::atomic<bool> m_bRunning;

		EngineMode m_eMode;

		static EasyObject* m_poScene; // Scene object
	};
}
