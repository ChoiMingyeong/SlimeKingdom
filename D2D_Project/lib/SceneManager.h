#pragma once

typedef map<string, Scene*>::iterator SceneIter;
class SceneManager : public Singleton<SceneManager>
{
public:
	SceneManager();

private:
	map<string, Scene*> m_pSceneList;
	SceneIter m_NowSceneIter;

public:
	//Scene을 추가한다.
	void CreateScene(string scene_name);
	//현재 Scene을 원하는 Scene으로 변경한다.
	void ChangeScene(string scene_name);
	//현재 Scene을 받아온다.
	Scene* GetNowScene();
	//현재 Scene의 이름을 받아온다.
	string GetNowSceneName();

	//원하는 Scene을 받아온다.
	Scene* GetScene(string scene_name);

	//현재 Scene을 갱신한다.
	void Update();
	//현재 Scene의 GameObject들을 화면에 그린다.
	void Draw();

	void Init();

};

