#pragma once

class Sprite
{
public:
	Sprite(const WCHAR* sheet_name, D2D1_RECT_F rect, D2D1_POINT_2F origin, float delay = 1.0f);

public:
	const WCHAR* m_SheetName;		//��Ʈ�� �ҷ����� ���� �ʿ��� ID
	D2D1_RECT_F m_SpriteRect;		//��Ʈ���� �߶�� ��ġ(StartPoint(left, top), EndPoint(right, bottom)
	D2D1_POINT_2F m_OriginPos;		//��������Ʈ�� ���� ������

	D2D1_RECT_F m_CollisionRect;	//��� �� �ݶ��̴� ��ġ
	float m_Delay;
};