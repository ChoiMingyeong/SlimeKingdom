#pragma once

class Animation
{
public:
	Animation(vector<Sprite*> sprites);

public:
	vector<Sprite*> m_pSprites;
	float m_Speed;
	float m_TotalDelay;
	//int m_FrameLimit = 20;

	bool m_IsLoop;
	int m_NowIndex;

public:
	void Update();
	float GetProgress();
	Sprite* GetNowSprite();
};