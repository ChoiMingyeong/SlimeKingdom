#include "pch.h"
#include "UI.h"

UI::UI(Object* parent)
	:m_MyScene(MySceneManager->GetNowScene())
{
	if (parent != nullptr)
	{
		m_Parent = parent;
	}

	m_MyScene->m_pUIManager->ResisterObserver(this);
}

UI::~UI()
{

}

void UI::Update()
{
}

void UI::Draw()
{
}
