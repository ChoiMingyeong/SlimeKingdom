#pragma once

class GameManager;

class GameProcess : public Singleton<GameProcess>
{
public:
	void Start();
	void Update();

public:
 	//GameObject* A;
 	//GameObject* B;
 	//GameObject* C;
    //TextUI* TestTextUI;

private:
	GameManager* m_pGameManager;

};

