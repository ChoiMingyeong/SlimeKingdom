#include "pch.h"
#include "SceneManager.h"

SceneManager::SceneManager()
{
	//Scene 목록 초기화
	m_pSceneList.clear();

	//첫번째 Scene 추가
	CreateScene("Scene_0");
	m_NowSceneIter = m_pSceneList.begin();
}

void SceneManager::CreateScene(string scene_name)
{
	m_pSceneList.insert(make_pair(scene_name, new Scene()));
}

void SceneManager::ChangeScene(string scene_name)
{
	for (SceneIter iter = m_pSceneList.begin(); iter!=m_pSceneList.end(); iter++)
	{
		if ((*iter).first == scene_name)
		{
			m_NowSceneIter = iter;
			break;
		}
	}
}

Scene* SceneManager::GetNowScene()
{
	return (*m_NowSceneIter).second;
}

string SceneManager::GetNowSceneName()
{
	return (*m_NowSceneIter).first;
}

Scene* SceneManager::GetScene(string scene_name)
{
	for (SceneIter iter = m_pSceneList.begin(); iter != m_pSceneList.end(); iter++)
	{
		if ((*iter).first == scene_name)
		{
			return (*iter).second;
		}
	}

	return nullptr;
}

void SceneManager::Update()
{
	GetNowScene()->Update();
}

void SceneManager::Draw()
{
	GetNowScene()->Draw();
}

void SceneManager::Init()
{
	GetNowScene()->Init();
}
