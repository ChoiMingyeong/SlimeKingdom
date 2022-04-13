#include "pch.h"
#include "Renderer.h"

Renderer::Renderer(Object* parent)
	: m_pSprite(nullptr)
{
	m_Size.SetValue(100, 100);
	if (parent != nullptr)
	{
		m_Parent = parent;
	}
}

void Renderer::Draw()
{
	if (m_Active && m_Visible)
	{
		MyEngine->SetTransform((m_Parent->GetTransfrom() + m_Transform).GetSR());
		D2D1_POINT_2F drawPoint = { m_Parent->GetTransfrom().Position.x, m_Parent->GetTransfrom().Position.y };
		if (m_pSprite == nullptr)
		{
			MyEngine->DrawRectangle(drawPoint, m_Size.m_Width, m_Size.m_Height);
		}
		else
		{
			MyEngine->DrawBitmap(this);
		}
		MyEngine->SetTransform(D2D1::Matrix3x2F::Identity());
	}
}

void Renderer::SetSprite(Sprite* p_sprite)
{
	m_pSprite = p_sprite;
	float width = m_pSprite->m_SpriteRect.right - m_pSprite->m_SpriteRect.left;
	float height = m_pSprite->m_SpriteRect.bottom - m_pSprite->m_SpriteRect.top;

	m_Size.m_Width = width;
	m_Size.m_Height = height;
}
