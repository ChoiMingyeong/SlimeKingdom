#include "pch.h"
#include "Animation.h"

Animation::Animation(vector<Sprite*> sprites)
	:m_Speed(1.0f), m_NowIndex(0), m_TotalDelay(0), m_IsLoop(true)
{
	m_pSprites = sprites;
}

void Animation::Update()
{
	m_TotalDelay +=  m_Speed / GetNowSprite()-> m_Delay;
	if (m_TotalDelay >= (m_NowIndex + 1))
	{
		++m_NowIndex;
		m_NowIndex %= m_pSprites.size();

		if (m_IsLoop)
		{
			m_TotalDelay = 0.0f;
		}
		else
		{
			m_NowIndex = m_pSprites.size() - 1;
			m_TotalDelay = m_Speed * m_pSprites.size();
		}
	}
}

float Animation::GetProgress()
{
	float delay = m_TotalDelay;
	return 0;
}

Sprite* Animation::GetNowSprite()
{
	return m_pSprites.at(m_NowIndex);
}
