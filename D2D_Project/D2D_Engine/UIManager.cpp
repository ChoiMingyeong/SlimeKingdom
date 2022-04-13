#include "pch.h"
#include "UIManager.h"

typedef vector<UI*>::iterator observer_iter;

UIManager::UIManager()
{
	m_UIs.clear();
}

UIManager::~UIManager()
{
	for (auto obj : m_UIs)
	{
		delete obj;
	}
	m_UIs.clear();
}

void UIManager::UpdateObserver()
{
}

void UIManager::ResisterObserver(UI* observer)
{
	m_UIs.push_back(observer);
}

void UIManager::RemoveObserver(UI* observer)
{
	for (observer_iter it = m_UIs.begin(); it != m_UIs.end(); it++)
	{
		if (*it == observer)
		{
			m_UIs.erase(it);
			break;
		}
	}
}

void UIManager::Draw()
{
	for (auto obj : m_UIs)
	{
		if (obj->m_Active && obj->m_Visible)
		{
			obj->Draw();
		}
	}
}
