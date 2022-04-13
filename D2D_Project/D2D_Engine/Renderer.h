#pragma once

class Renderer : public Object
{
	//생성자&소멸자
public:
	Renderer(Object* parent = nullptr);

	//멤버 변수
public:
	Size m_Size;
	Sprite* m_pSprite;

	//멤버 함수
public:
	virtual void Draw();
	void SetSprite(Sprite* p_sprite);
};

