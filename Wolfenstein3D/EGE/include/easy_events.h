#pragma once

#include <Windows.h>

#include "utils.h"

namespace ege
{
	// Key object
	struct Key
	{
		bool bPressed;
		bool bReleased;
		bool bHeld;
	};

	// Mouse object
	struct Mouse
	{
		Vector2<int> vPosition;
		int nMouseWheel;
		Key kButtons[3];
	};

	class EasyEvents
	{
	public:
		EasyEvents();
		void HandleKeyboard(UINT uMsg, WPARAM wParam, LPARAM lParam); // Handle keyboard states
		void ProcessKeyboard(); // Process keyboard changes
		void HandleMouse(UINT uMsg, WPARAM wParam, LPARAM lParam); // Handle mouse events states
		void ProcessMouse(); // Process mouse changes

	public:
		static bool GetKeyPressed(UINT unKeyCode); // Is key pressed
		static bool GetKeyReleased(UINT unKeyCode); // Is key released
		static bool GetKeyHeld(UINT unKeyCode); // Is key held

	public:
		static void HandleEngineEvents(std::string sEvent, ...);

	private:
		static Key m_kKeys[0xFF]; // Keys array
		static Key m_kUnprocessedKeys[0xFF]; // Unprocessed keys array

		Mouse m_mMouse; // Mouse
	};
}