#include "stdafx.h"
#include "GameManager.h"

GameManager::GameManager()
	: m_pGameState(nullptr)
{

}
GameManager::~GameManager(){}

void GameManager::Initialize()
{
	/// ����, ������ �� ���� �Ŵ��� ���� �� �ʱ�ȭ

	/// Player, Monster, Map �� �ʱ�ȭ

	m_pGameState = new GameState;

}

void GameManager::GameLoop()
{
	switch (m_pGameState->GetGameState())
	{
		case eGameState::Intro:
		{
			// ��Ʈ�� ȭ��
			m_pGameState->Intro();
		}
		break;
		case eGameState::MainScene:
		{
			// ���� Ÿ��Ʋ ȭ��
			m_pGameState->MainScene();
		}
		break;
		case eGameState::InGame:
		{
			// �ΰ��� ȭ��
			m_pGameState->InGame();
		}
		break;
		case eGameState::GameOver:
		{
			// ���� ����(������ ����)
			m_pGameState->GameOver();
		}
		break;
		case eGameState::GameEnding:
		{
			// ���� ����
			m_pGameState->GameEnding();
		}
		default:
		{

		}
		break;
	}

	Update();
}

void GameManager::Update()
{
	// �� ���ӻ��¸� ������Ʈ �Ѵ�.


	// ���ӿ��� üũ
	m_pGameState->CheckGameOver();

}
