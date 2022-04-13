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
		//본인이 꺼져있으면 다음 오브젝트 체크
		if (!obj->m_Active)	continue;

		obj->ResetHit();

		for (int i = 0; i < m_GameObjects.size(); i++)
		{
			//체크 대상이 본인이면 continue
			if (m_GameObjects[i] == obj)	continue;
			//체크 대상이 꺼져있으면 continue
			if (!m_GameObjects[i]->m_Active)	continue;
			//체크 대상의 Hit Objects에 이미 본인이 들어가있으면 continue
			for (auto iter : m_GameObjects[i]->m_pCollider->m_HitObjects)
			{
				if (iter == obj)	continue;
			}

			obj->CheckCollision(m_GameObjects[i]);
		}
	}
}
