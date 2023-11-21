
#include "easy_events.h"

using namespace ege;

Key EasyEvents::m_kKeys[0xFF]; // Keys array
Key EasyEvents::m_kUnprocessedKeys[0xFF]; // Unprocessed keys array

EasyEvents::EasyEvents()
{
	memset(m_kKeys, 0, sizeof(m_kKeys));
	memset(m_kUnprocessedKeys, 0, sizeof(m_kUnprocessedKeys));
}

// Handle keyboard events
void EasyEvents::HandleKeyboard(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (lParam >> 31 == 0) // Is key down
		m_kUnprocessedKeys[wParam].bPressed = true;
	else // Key is up
		m_kUnprocessedKeys[wParam].bReleased = true;
}

// Update keyboard states
void EasyEvents::ProcessKeyboard()
{
	for (int i = 0; i < 0xFF; i++)
	{
		// Handle key press
		m_kKeys[i].bPressed = false; // Reset key
		if (!m_kKeys[i].bHeld) // Was key up
		{
			m_kKeys[i].bPressed = m_kUnprocessedKeys[i].bPressed;
			m_kKeys[i].bHeld = m_kUnprocessedKeys[i].bPressed;
		}
		m_kUnprocessedKeys[i].bPressed = false; // Reset

		// Handle key release
		m_kKeys[i].bReleased = false; // Reset key
		if (m_kKeys[i].bHeld) // Was key down
		{
			m_kKeys[i].bReleased = m_kUnprocessedKeys[i].bReleased;
			m_kKeys[i].bHeld = !m_kUnprocessedKeys[i].bReleased;
		}
		m_kUnprocessedKeys[i].bReleased = false; // Reset
	}
}

// Is key pressed
bool EasyEvents::GetKeyPressed(UINT unKeyCode)
{
	return m_kKeys[unKeyCode].bPressed;
}

// Is key released
bool EasyEvents::GetKeyReleased(UINT unKeyCode)
{
	return m_kKeys[unKeyCode].bReleased;
}

// Is key held
bool EasyEvents::GetKeyHeld(UINT unKeyCode)
{
	return m_kKeys[unKeyCode].bHeld;
}

// Handle mouse events
void EasyEvents::HandleMouse(UINT uMsg, WPARAM wParam, LPARAM lParam)
{

}