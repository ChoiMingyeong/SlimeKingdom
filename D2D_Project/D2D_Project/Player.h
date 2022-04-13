#pragma once
#include "GameObject.h"
#include "GameDefinition.h"

class Projectile;

class Player : public GameObject
{
public:
	Player();
	virtual ~Player();

private:
	POINT m_Pos;					// ��ġ
	int m_Hp;						// ü��
	int m_Life;						// ������
	float m_MoveSpeed;				// �̵��ӷ�

	eState m_eState;				// ����
	eElementType m_eElementType;	// �Ӽ�
	float m_SkillStamina;			// ��ų������
	bool m_DoSkill;					// ��ų ��� ���ΰ�

	Projectile* m_Projectile;		// Player�� �߻��ϴ� ����ü

public:
	void Move();
	void AbsorbAttack();
	void UseSkill();
};

