#pragma once

// Playe, Monster의 상태
enum class eState
{
	Idle,			// 대기
	Move,			// 이동
	Absorb,			// 흡수모션
	BeAttacked,		// 피격모션

	GetFire,		// 불 흡수상태
	GetWater,		// 물 흡수상태
	GetLeaf,		// 풀 흡수상태

	ShootFire,		// 불 발사
	ShootWater,		// 물 발사
	ShootLeaf,		// 풀 발사

	MAX_STATE
};

enum class eElementType
{
	Default,		// 무속성 상태
	Fire,			// 불
	Water,			// 물
	Leaf,			// 풀

	MAX_PROPERTY
};
