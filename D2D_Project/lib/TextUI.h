#pragma once

class TextUI : public UI
{
public:
	virtual ~TextUI();

public:
	const WCHAR* m_Text;

public:
	virtual void Update();
	virtual void Draw();
};

