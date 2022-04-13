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
	POINT m_Pos;					// 위치
	int m_Hp;						// 체력
	int m_Life;						// 라이프
	float m_MoveSpeed;				// 이동속력

	eState m_eState;				// 동작
	eElementType m_eElementType;	// 속성
	float m_SkillStamina;			// 스킬게이지
	bool m_DoSkill;					// 스킬 사용 중인가

	Projectile* m_Projectile;		// Player가 발사하는 투사체

public:
	void Move();
	void AbsorbAttack();
	void UseSkill();
};

