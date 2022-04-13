#include "pch.h"
#include "Scene.h"

Scene::Scene()
	:m_pGameObjectManager(nullptr), m_pUIManager(nullptr), m_pCamera(nullptr)
{}

Scene::~Scene()
{
	delete m_pGameObjectManager;
	delete m_pUIManager;
	delete m_pCamera;
}

void Scene::Init()
{
	m_pGameObjectManager = new GameObjectManager();
	m_pUIManager = new UIManager();
	m_pCamera = new Camera();
}

void Scene::Update()
{
	m_pGameObjectManager->UpdateObserver();
	m_pGameObjectManager->CheckCollision();
}

void Scene::Draw()
{
	m_pGameObjectManager->Draw();
	m_pUIManager->Draw();
}
