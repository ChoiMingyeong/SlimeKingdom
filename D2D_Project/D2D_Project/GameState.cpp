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
	// ��Ʈ�� ���� ������.
	m_pTempText->m_Text = _T("��Ʈ��");
	m_pTempText->m_Transform.Position = { 100, 100 };

	// ��Ʈ�� ȭ�� �����ְ� ����Ÿ��Ʋ ȭ������
	if (Input::InputKeyUp(VK_SPACE))
	{
		m_eGS = eGameState::MainScene;
	}
}

void GameState::MainScene()
{
	// ����Ÿ��Ʋ ȭ��
	m_pTempText->m_Text = _T("���� Ÿ��Ʋ ȭ��");
	m_pTempText->m_Transform.Position = { 100, 100 };

	// �����̽� ������ �ΰ�������
	if (Input::InputKeyUp(VK_SPACE))
	{
		m_eGS = eGameState::InGame;
	}
}

void GameState::InGame()
{
	/// �ΰ���
	m_pTempText->m_Text = _T("�ΰ��� ȭ�� : B Ű -> DBCount+ / N Ű -> Life-");
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
	// ���ӿ��� ȭ��
	m_pTempText->m_Text = _T("���ӿ���");
	m_pTempText->m_Transform.Position = { 100, 100 };

	// ���ӿ����� �����̽� ������ ����Ÿ��Ʋ ȭ������
	if (Input::InputKeyUp(VK_SPACE))
	{
		m_Life = 3;
		m_eGS = eGameState::MainScene;
	}
}

void GameState::GameEnding()
{
	// ���ӿ��� ȭ��
	m_pTempText->m_Text = _T("����Ŭ����");
	m_pTempText->m_Transform.Position = { 100, 100 };

	// ����Ÿ��Ʋ ȭ��
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
		// ���ӿ���
		m_eGS = eGameState::GameOver;
		return;
	}
	else
	{
		if (m_DBcount == MAX_DBCOUNT)
		{
			// ����Ŭ����
			m_eGS = eGameState::GameEnding;
			return;
		}
		else
		{
			// ���Ӽ���
		}
	}
}
