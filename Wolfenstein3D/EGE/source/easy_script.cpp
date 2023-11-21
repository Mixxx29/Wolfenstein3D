
#include "easy_script.h"

#include <string>

#include "utils.h"

using namespace ege;

EasyScript::EasyScript()
{
	
}

/************************************** Children ********************************************/

// Add child to object
void EasyScript::AddObject(EasyObject* poChild)
{
	m_peHost->AddObject(poChild);
}

// Remove child from object
void EasyScript::RemoveObject(int index)
{
	m_peHost->RemoveObject(index);
}

// Get child from object
EasyObject* EasyScript::GetChild(int index)
{
	return m_peHost->GetChild(index);
}

/**************************************** Scripts **********************************************/

// Add component to object
void EasyScript::AddScript(EasyScript* eScript)
{
	m_peHost->AddScript(eScript);
}

// Remove component from object
template <class T>
void EasyScript::RemoveScript()
{
	m_peHost->RemoveScript<T>();
}

/**************************************** Getters **********************************************/

// Get host object
EasyObject* EasyScript::GetHost()
{
	return m_peHost;
}

// Get object position
Vector2<float> EasyScript::GetPosition()
{
	return m_peHost->GetPosition();
}

// Get object size
Dimensions<float> EasyScript::GetSize()
{
	return m_peHost->GetSize();
}

/**************************************** Setters **********************************************/

// Set object
void EasyScript::SetHost(class EasyObject* peObject)
{
	if (m_peHost == nullptr)
	{
		m_peHost = peObject;
	}

	position = &peObject->position; // Object position
	size = &peObject->size; // Object size
}

// Set object position
void EasyScript::SetPosition(Vector2<float> vPosition)
{
	m_peHost->SetPosition(vPosition);
}

// Set object size
void EasyScript::SetSize(Dimensions<float> dSize)
{

	m_peHost->SetSize(dSize);
}

/**************************************** Wrappers **********************************************/

// Debug to console
void EasyScript::Debug(std::string sString)
{
	EasyUtils::Debug(sString);
}

// Debug to console
void EasyScript::Debug(int nNumber)
{
	EasyUtils::Debug(nNumber);
}