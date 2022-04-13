#include "pch.h"
#include "TextUI.h"

TextUI::~TextUI()
{
}

void TextUI::Update()
{
}

void TextUI::Draw()
{
	if (m_Active && m_Visible)
	{
		MyEngine->SetTransform((m_Parent->GetTransfrom() + m_Transform).GetSR());
		D2D1_POINT_2F drawPoint = { m_Parent->GetTransfrom().Position.x, m_Parent->GetTransfrom().Position.y };
		if (m_Text != nullptr)
		{
			MyEngine->DrawTextFormat(m_Text, drawPoint.x, drawPoint.y);
		}
		MyEngine->SetTransform(D2D1::Matrix3x2F::Identity());
	}
}
