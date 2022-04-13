#pragma once

// Playe, Monster�� ����
enum class eState
{
	Idle,			// ���
	Move,			// �̵�
	Absorb,			// ������
	BeAttacked,		// �ǰݸ��

	GetFire,		// �� �������
	GetWater,		// �� �������
	GetLeaf,		// Ǯ �������

	ShootFire,		// �� �߻�
	ShootWater,		// �� �߻�
	ShootLeaf,		// Ǯ �߻�

	MAX_STATE
};

enum class eElementType
{
	Default,		// ���Ӽ� ����
	Fire,			// ��
	Water,			// ��
	Leaf,			// Ǯ

	MAX_PROPERTY
};
