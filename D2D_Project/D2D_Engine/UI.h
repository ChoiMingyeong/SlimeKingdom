#pragma once

class UI : public Object, public Observer
{
public:
	UI(Object* parent = nullptr);
	virtual ~UI();

public:
	Scene* m_MyScene;

public:
	virtual void Update();
	virtual void Draw();
};

