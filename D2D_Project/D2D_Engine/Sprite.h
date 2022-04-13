#pragma once

class Sprite
{
public:
	Sprite(const WCHAR* sheet_name, D2D1_RECT_F rect, D2D1_POINT_2F origin, float delay = 1.0f);

public:
	const WCHAR* m_SheetName;		//시트를 불러오기 위해 필요한 ID
	D2D1_RECT_F m_SpriteRect;		//시트에서 잘라올 위치(StartPoint(left, top), EndPoint(right, bottom)
	D2D1_POINT_2F m_OriginPos;		//스프라이트를 찍을 기준점

	D2D1_RECT_F m_CollisionRect;	//모션 별 콜라이더 위치
	float m_Delay;
};