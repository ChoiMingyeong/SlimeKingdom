#include "stdafx.h"
#include "GameState.h"

GameState::GameState()
	:m_eGS(eGameState::Intro), m_DBcount(0), m_Life(3), m_pTempText(nullptr)
{
	m_pTempText = new TextUI;
	m_pTempText->m_Text = _T("");

	m_pBCount = new TextUI;
	m_pBCount->m_Text = _T("");

	m_pNCount = new TextUI;
	m_pNCount->m_Text = _T("");
}

GameState::~GameState() {}

void GameState::Intro()
{
	// 인트로 씬을 보여줌.
	m_pTempText->m_Text = _T("인트로");
	m_pTempText->m_Transform.Position = { 100, 100 };

	// 인트로 화면 보여주고 메인타이틀 화면으로
	if (Input::InputKeyUp(VK_SPACE))
	{
		m_eGS = eGameState::MainScene;
	}
}

void GameState::MainScene()
{
	// 메인타이틀 화면
	m_pTempText->m_Text = _T("메인 타이틀 화면");
	m_pTempText->m_Transform.Position = { 100, 100 };

	// 스페이스 누르면 인게임으로
	if (Input::InputKeyUp(VK_SPACE))
	{
		m_eGS = eGameState::InGame;
	}
}

void GameState::InGame()
{
	/// 인게임
	m_pTempText->m_Text = _T("인게임 화면 : B 키 -> DBCount+ / N 키 -> Life-");
	m_pTempText->m_Transform.Position = { 100, 100 };

	m_strBCount = to_wstring(m_DBcount);
	m_pBCount->m_Text = m_strBCount.c_str();
	m_pBCount->m_Transform.Position = { 100, 200 };

	m_strNCount = to_wstring(m_Life);
	m_pNCount->m_Text = m_strNCount.c_str();
	m_pNCount->m_Transform.Position = { 100, 300 };


	if (Input::InputKeyUp(VK_B))
	{
		m_DBcount++;
	}

	if (Input::InputKeyDown(VK_N))
	{
		m_Life--;
	}
}

void GameState::GameOver()
{
	// 게임오버 화면
	m_pTempText->m_Text = _T("게임오버");
	m_pTempText->m_Transform.Position = { 100, 100 };

	// 게임오버시 스페이스 누르면 메인타이틀 화면으로
	if (Input::InputKeyUp(VK_SPACE))
	{
		m_Life = 3;
		m_eGS = eGameState::MainScene;
	}
}

void GameState::GameEnding()
{
	// 게임엔딩 화면
	m_pTempText->m_Text = _T("게임클리어");
	m_pTempText->m_Transform.Position = { 100, 100 };

	// 메인타이틀 화면
	if (Input::InputKeyUp(VK_SPACE))
	{
		m_DBcount = 0;
		m_eGS = eGameState::MainScene;
	}
}

void GameState::CheckGameOver()
{
	if (m_Life <= 0)
	{
		// 게임오버
		m_eGS = eGameState::GameOver;
		return;
	}
	else
	{
		if (m_DBcount == MAX_DBCOUNT)
		{
			// 게임클리어
			m_eGS = eGameState::GameEnding;
			return;
		}
		else
		{
			// 게임속행
		}
	}
}
