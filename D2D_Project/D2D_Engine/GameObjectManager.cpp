#include "pch.h"
#include "GameObjectManager.h"

typedef vector<GameObject*>::iterator observer_iter;

GameObjectManager::GameObjectManager()
{
	m_GameObjects.clear();
}

GameObjectManager::~GameObjectManager()
{
	for (auto obj : m_GameObjects)
	{
		delete obj;
	}
	m_GameObjects.clear();
}

void GameObjectManager::UpdateObserver()
{
	for (auto obj : m_GameObjects)
	{
		obj->Update();
	}
}

void GameObjectManager::ResisterObserver(GameObject* observer)
{
	m_GameObjects.push_back(observer);
}

void GameObjectManager::RemoveObserver(GameObject* observer)
{
	for (observer_iter it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	{
		if (*it == observer)
		{
			m_GameObjects.erase(it);
			break;
		}
	}
}

void GameObjectManager::Draw()
{
	for (auto obj : m_GameObjects)
	{
		if (obj->m_Active && obj->m_Visible)
		{
			obj->Draw();
		}
	}
}

void GameObjectManager::CheckCollision()
{
	for (auto obj : m_GameObjects)
	{
		//������ ���������� ���� ������Ʈ üũ
		if (!obj->m_Active)	continue;

		obj->ResetHit();

		for (int i = 0; i < m_GameObjects.size(); i++)
		{
			//üũ ����� �����̸� continue
			if (m_GameObjects[i] == obj)	continue;
			//üũ ����� ���������� continue
			if (!m_GameObjects[i]->m_Active)	continue;
			//üũ ����� Hit Objects�� �̹� ������ �������� continue
			for (auto iter : m_GameObjects[i]->m_pCollider->m_HitObjects)
			{
				if (iter == obj)	continue;
			}

			obj->CheckCollision(m_GameObjects[i]);
		}
	}
}
