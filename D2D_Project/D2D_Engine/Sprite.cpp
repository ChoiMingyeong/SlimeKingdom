#include "pch.h"
#include "Sprite.h"

Sprite::Sprite(const WCHAR* sheet_name, D2D1_RECT_F rect, D2D1_POINT_2F origin, float delay)
	:m_SheetName(sheet_name), m_SpriteRect(rect), m_OriginPos(origin), m_Delay(delay)
{}