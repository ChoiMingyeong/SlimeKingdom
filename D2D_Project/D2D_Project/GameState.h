#pragma once

#define MAX_DBCOUNT	7

enum class eGameState
{
	// ���� ����
	Intro,
	MainScene,

	// ���� ����
	InGame,

	// ���� ��
	GameOver,
	GameEnding,

	GameState_Max
};

class GameState
{
public:
	GameState();
	~GameState();

private:
	eGameState m_eGS;

	int m_DBcount;				// �ӽ� Ŭ���� ����
	int m_Life;					// �ӽ� ���ӿ��� ����
	TextUI* m_pTempText;		// �ӽ� �ؽ�Ʈ

	TextUI* m_pBCount;			// �ӽ� �ؽ�Ʈ
	TextUI* m_pNCount;			// �ӽ� �ؽ�Ʈ

	wstring m_strBCount;
	wstring m_strNCount;

public:
	void Intro();
	void MainScene();
	void InGame();
	void GameOver();
	void GameEnding();

	eGameState GetGameState() const { return m_eGS; }
	void CheckGameOver();

};

