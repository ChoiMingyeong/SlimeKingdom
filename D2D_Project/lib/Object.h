#pragma once

class Object
{
public:
	Object();

public:
	Transform m_Transform;	//위치, 회전, 크기의 값
	bool m_Active;		// 활성화 & 비활성화
	bool m_Visible;		// 보임? 안보임?

	Object* m_Parent;	//부모 객체

public:
	virtual void Draw() = 0;
	virtual Transform GetTransfrom();
};

