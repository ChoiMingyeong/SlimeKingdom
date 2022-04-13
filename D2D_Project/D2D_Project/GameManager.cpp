#include "stdafx.h"
#include "GameManager.h"

GameManager::GameManager()
	: m_pGameState(nullptr)
{

}
GameManager::~GameManager(){}

void GameManager::Initialize()
{
	/// 사운드, 데이터 등 각종 매니져 생성 및 초기화

	/// Player, Monster, Map 등 초기화

	m_pGameState = new GameState;

}

void GameManager::GameLoop()
{
	switch (m_pGameState->GetGameState())
	{
		case eGameState::Intro:
		{
			// 인트로 화면
			m_pGameState->Intro();
		}
		break;
		case eGameState::MainScene:
		{
			// 메인 타이틀 화면
			m_pGameState->MainScene();
		}
		break;
		case eGameState::InGame:
		{
			// 인게임 화면
			m_pGameState->InGame();
		}
		break;
		case eGameState::GameOver:
		{
			// 게임 오버(라이프 없음)
			m_pGameState->GameOver();
		}
		break;
		case eGameState::GameEnding:
		{
			// 게임 엔딩
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
	// 각 게임상태를 업데이트 한다.


	// 게임오버 체크
	m_pGameState->CheckGameOver();

}
