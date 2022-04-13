#pragma once

class Renderer : public Object
{
	//������&�Ҹ���
public:
	Renderer(Object* parent = nullptr);

	//��� ����
public:
	Size m_Size;
	Sprite* m_pSprite;

	//��� �Լ�
public:
	virtual void Draw();
	void SetSprite(Sprite* p_sprite);
};

