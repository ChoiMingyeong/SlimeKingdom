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
	//Scene�� �߰��Ѵ�.
	void CreateScene(string scene_name);
	//���� Scene�� ���ϴ� Scene���� �����Ѵ�.
	void ChangeScene(string scene_name);
	//���� Scene�� �޾ƿ´�.
	Scene* GetNowScene();
	//���� Scene�� �̸��� �޾ƿ´�.
	string GetNowSceneName();

	//���ϴ� Scene�� �޾ƿ´�.
	Scene* GetScene(string scene_name);

	//���� Scene�� �����Ѵ�.
	void Update();
	//���� Scene�� GameObject���� ȭ�鿡 �׸���.
	void Draw();

	void Init();

};

