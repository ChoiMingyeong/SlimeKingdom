#pragma once

/// <summary>
/// 게임의 전반전인 상태를 관리하는 클래스
/// 
/// 2021.02.09. KJ
/// 
/// </summary>

class GameManager
{
public:
	GameManager();
	~GameManager();

public:
	void Initialize();			// 게임 초기화
	void GameLoop();			// 게임 루프
	void Update();				// 각 상태를 업데이트함

private:
	GameState* m_pGameState;	// 게임 상태

};

