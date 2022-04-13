#pragma once

class Collision : public Object
{
public:
	Collision(Object* parent = nullptr);

public:
	Size m_Size;						//�浹ü�� ũ��
	vector<Object*> m_HitObjects;		//�ε��� ������Ʈ���� �����صδ� ����

public:
	virtual void CheckCollision(Collision* p_target);
	virtual void Draw();

	virtual void SetValue(Size);
	virtual PT4_Rect GetBoundingBox();
	virtual void ResetHit();
};

D2D_MATRIX_3X2_F GetTranslateMatrix(float dx, float dy);
D2D_MATRIX_3X2_F GetRotateMatrix(float angle);
D2D_MATRIX_3X2_F GetScaleMatrix(float x, float y);
D2D1_POINT_2F GetTransform(D2D1_POINT_2F& source, Transform transform);

D2D1_POINT_2F operator*(D2D1_POINT_2F& pt, D2D_MATRIX_3X2_F& matrix);
D2D1_POINT_2F operator+(D2D1_POINT_2F& pt1, D2D1_POINT_2F& pt2);
D2D1_POINT_2F operator/(D2D1_POINT_2F& pt, float value);