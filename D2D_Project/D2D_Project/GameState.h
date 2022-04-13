#pragma once

#define MAX_DBCOUNT	7

enum class eGameState
{
	// 게임 시작
	Intro,
	MainScene,

	// 게임 진행
	InGame,

	// 게임 끝
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

	int m_DBcount;				// 임시 클리어 조건
	int m_Life;					// 임시 게임오버 조건
	TextUI* m_pTempText;		// 임시 텍스트

	TextUI* m_pBCount;			// 임시 텍스트
	TextUI* m_pNCount;			// 임시 텍스트

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

