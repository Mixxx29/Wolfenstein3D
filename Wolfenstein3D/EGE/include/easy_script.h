#pragma once

#include "easy_object.h"
#include "easy_events.h"
#include "easy_window.h"
#include "easy_graphics.h"
#include "utils.h"

namespace ege
{
	class EasyScript
	{
	public:
		EasyScript();
		void Emit(std::string sEvent); // Emit event

	public: // Virtual
		virtual void OnStart() {}; // On start callback
		virtual void OnUpdate(float fDeltaTime) {}; // On update callback

	protected: // Children
		void AddObject(class EasyObject* poChild); // Add child to object
		void RemoveObject(int index); // Remove child from object
		EasyObject* GetChild(int index); // Get child from object

	protected: // Script
		void AddScript(EasyScript* eScript); // Add script to object
		template <class T> void RemoveScript(); // Remove script from object
		template <class T> T* GetScript(); // Get script from object

	public: // Getters
		class EasyObject* GetHost(); // Get host object

	protected: // Getters
		Vector2<float> GetPosition(); // Get object position
		Dimensions<float> GetSize(); // Get object size

	public: // Setters
		void SetHost(class EasyObject* peObject); // Set host object

	protected: // Setters
		void SetPosition(Vector2<float> vPosition); // Set object position
		void SetSize(Dimensions<float> dSize); // Set object size

	protected: // Wrappers
		void Debug(std::string sString); // Debug to console
		void Debug(int nNumber); // Debug to console

	public:
		Vector2<float>* position; // Object position
		Dimensions<float>* size; // Object size

	private:
		EasyObject* m_peHost;
	};

	// Get component from object
	template <class T>
	T* EasyScript::GetScript()
	{
		return m_peHost.template GetScript<T>();
	}
}
