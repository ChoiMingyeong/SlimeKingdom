#pragma once

/// <summary>
/// ������ �������� ���¸� �����ϴ� Ŭ����
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
	void Initialize();			// ���� �ʱ�ȭ
	void GameLoop();			// ���� ����
	void Update();				// �� ���¸� ������Ʈ��

private:
	GameState* m_pGameState;	// ���� ����

};

