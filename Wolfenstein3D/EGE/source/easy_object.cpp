
#include "easy_object.h"

using namespace ege;

EasyObject::EasyObject(std::string sName)
{
	// Set object name 
	m_sName = sName;

	// Clear scripts
	m_mScripts.clear();

	// Initialize object position
	position = { 0, 0 };
	
	// Initialize object size
	size = { 100.0f, 100.0f };
}

// Object on start event
void EasyObject::OnStart()
{
	// Trigger on start event for every script
	for (auto it : m_mScripts)
		it.second->OnStart();

	// Trigger on start event for every child
	for (auto it : m_mChildren)
		it.second->OnStart();
}

// Object on update event
void EasyObject::OnUpdate(float fDeltaTime)
{
	for (auto it : m_mScripts)
		it.second->OnUpdate(fDeltaTime);

	for (auto it : m_mChildren)
		it.second->OnUpdate(fDeltaTime);
}

/************************************** Children ********************************************/

// Add child to object
void EasyObject::AddObject(EasyObject* poChild)
{
	std::string sName = poChild->GetName();

	if (m_mChildren.find(sName) != m_mChildren.end())
		return;

	m_mChildren.insert({ sName, poChild });
}

// Remove child from object
void EasyObject::RemoveObject(int index)
{

}

// Get child from object
EasyObject* EasyObject::GetChild(int index)
{
	return nullptr;
}

// Find child by name
EasyObject* EasyObject::GetChild(std::string sName)
{
	auto pair = m_mChildren.find(sName);
	if (pair == m_mChildren.end()) return nullptr;

	return pair->second;
}

// Find object by name
EasyObject* EasyObject::Find(std::string sName)
{
	if (m_sName == sName) return this;
	
	EasyObject* po = nullptr;;
	for (auto it : m_mChildren)
		if (po = it.second->Find(sName)) 
			return po;

	return nullptr;
}


/*************************************** Scripts ********************************************/

// Add script to object
void EasyObject::AddScript(EasyScript* eScript)
{
	// Get class name
	size_t unCode = typeid(*eScript).hash_code();

	// Check if script already exist
	if (m_mScripts.find(unCode) != m_mScripts.end())
		return;

	// Add new script
	m_mScripts.insert({ unCode, eScript });

	// Set object
	eScript->SetHost(this);
}

// Remove script from object
template <typename T>
void EasyObject::RemoveScript()
{

}

/**************************************** Getters **********************************************/

// Get object name
std::string EasyObject::GetName()
{
	return m_sName;
}

// Get object parent
EasyObject* EasyObject::GetParent()
{
	return m_poParent;
}

// Get object position
Vector2<float> EasyObject::GetPosition()
{
	return position;
}

// Get object size
Dimensions<float> EasyObject::GetSize()
{
	return size;
}

/**************************************** Setters **********************************************/

// Set object parent
void EasyObject::SetParent(EasyObject* peObject)
{
	m_poParent = peObject;
}

// Set object position
void EasyObject::SetPosition(Vector2<float> vPosition)
{
	position = vPosition;
}

// Set object size
void EasyObject::SetSize(Dimensions<float> dSize)
{
	size = dSize;
}