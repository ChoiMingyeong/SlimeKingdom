#pragma once

struct Size
{
	float m_Width;
	float m_Height;

	void SetValue(float w, float h)
	{
		m_Width = w;
		m_Height = h;
	}
};

struct PT4_Rect
{
	D2D_POINT_2F pt[4];
};