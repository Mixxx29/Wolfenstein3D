#pragma once

#include <map>

#include "utils.h"
#include "easy_script.h"

namespace ege
{
	class EasyObject
	{
	public:
		EasyObject(std::string sName);
		void OnStart(); // Object on start event
		void OnUpdate(float fDeltaTime); // Object on update event

	public: // Children
		void AddObject(EasyObject* poChild); // Add child to object
		void RemoveObject(int index); // Remove child from object
		EasyObject* GetChild(int index); // Get child from object
		EasyObject* GetChild(std::string sName); // Find direct child by name
		EasyObject* Find(std::string sName); // Find child by name

	public: // Scripts
		void AddScript(class EasyScript* peScript); // Add script to object
		template <class T> void RemoveScript(); // Remove script from object
		template <class T> T* GetScript(); // Get script from object

	public: // Getters
		std::string GetName(); // Get object name
		EasyObject* GetParent(); // Get object parent
		Vector2<float> GetPosition(); // Get object position
		Dimensions<float> GetSize(); // Get object size

	public: // Setters
		void SetParent(EasyObject* peObject);
		void SetPosition(Vector2<float> vPosition); // Set object position
		void SetSize(Dimensions<float> dSize); // Set object size

	public:
		Vector2<float> position; // Object position
		Dimensions<float> size; // Object size

	private:
		std::string m_sName; // Object name

		EasyObject* m_poParent; // Object parent

		std::map<std::string, EasyObject*> m_mChildren; // Object children
		std::map<size_t, EasyScript*> m_mScripts; // Object scripts
	};

	// Get script from object
	template <class T>
	T* EasyObject::GetScript()
	{
		size_t unCode = typeid(T).hash_code();

		auto pair = m_mScripts.find(unCode);
		if (pair == m_mScripts.end()) return nullptr;

		return (T*)pair->second;
	}
}