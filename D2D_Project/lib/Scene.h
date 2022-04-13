#pragma once

class Scene
{
public:
	Scene();
	~Scene();

public:
	GameObjectManager* m_pGameObjectManager;
	UIManager* m_pUIManager;
	Camera* m_pCamera;

public:
	void Init();

	void Update();
	void Draw();
};

