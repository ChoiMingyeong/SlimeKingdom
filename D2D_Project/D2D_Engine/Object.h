#pragma once

class Object
{
public:
	Object();

public:
	Transform m_Transform;	//��ġ, ȸ��, ũ���� ��
	bool m_Active;		// Ȱ��ȭ & ��Ȱ��ȭ
	bool m_Visible;		// ����? �Ⱥ���?

	Object* m_Parent;	//�θ� ��ü

public:
	virtual void Draw() = 0;
	virtual Transform GetTransfrom();
};

