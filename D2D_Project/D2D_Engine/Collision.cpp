#include "pch.h"
#include "Collision.h"

Collision::Collision(Object* parent)
{
	m_Size.SetValue(100, 100);
}

void Collision::CheckCollision(Collision* p_target)
{
	//Active가 켜져있으면 체크
	if (m_Active)
	{
		//BoxCollider면
		if (dynamic_cast<BoxCollider*>(this) != nullptr)
		{
			BoxCollider* pTempBoxCollider = dynamic_cast<BoxCollider*>(this);
			pTempBoxCollider->CheckCollision(p_target);
		}

		//CircleCollider면
		if (dynamic_cast<CircleCollider*>(this) != nullptr)
		{
			CircleCollider* pTempCircleCollider = dynamic_cast<CircleCollider*>(this);
			pTempCircleCollider->CheckCollision(p_target);
		}
	}
}

void Collision::Draw()
{
	//Active가 켜져있고 Visible 상태면 그린다
	if (m_Active && m_Visible)
	{
		//BoxCollider면
		if (dynamic_cast<BoxCollider*>(this) != nullptr)
		{
			BoxCollider* pTempBoxCollider = dynamic_cast<BoxCollider*>(this);
			pTempBoxCollider->Draw();
		}

		//CircleCollider면
		if (dynamic_cast<CircleCollider*>(this) != nullptr)
		{
			CircleCollider* pTempCircleCollider = dynamic_cast<CircleCollider*>(this);
			pTempCircleCollider->Draw();
		}
	}
}

void Collision::SetValue(Size size)
{
	m_Size = size;
}

PT4_Rect Collision::GetBoundingBox()
{
	D2D1_RECT_F myBB;
	myBB.left = m_Transform.Position.x - m_Size.m_Width / 2;
	myBB.top = m_Transform.Position.y - m_Size.m_Height / 2;
	myBB.right = m_Transform.Position.x + m_Size.m_Width / 2;
	myBB.bottom = m_Transform.Position.y + m_Size.m_Height / 2;

	Transform worldTransform = m_Parent->GetTransfrom() + m_Transform;

	PT4_Rect rect;
	rect.pt[0] = { myBB.left, myBB.top };
	rect.pt[1] = { myBB.right, myBB.top };
	rect.pt[2] = { myBB.right, myBB.bottom };
	rect.pt[3] = { myBB.left, myBB.bottom };

	for (int i = 0; i < 4; i++)
	{
		rect.pt[i] = GetTransform(rect.pt[i], worldTransform);
	}

	return rect;
}

void Collision::ResetHit()
{
	m_HitObjects.clear();
}

D2D_MATRIX_3X2_F GetTranslateMatrix(float dx, float dy)
{
	D2D_MATRIX_3X2_F tempMatrix;
	tempMatrix.m11 = 1;		tempMatrix.m12 = 0;
	tempMatrix.m21 = 0;		tempMatrix.m22 = 1;
	tempMatrix.dx = dx;		tempMatrix.dy = dy;

	return tempMatrix;
}

D2D_MATRIX_3X2_F GetRotateMatrix(float angle)
{
	D2D_MATRIX_3X2_F tempMatrix;
	tempMatrix.m11 = cosf(angle);		tempMatrix.m12 = -sinf(angle);
	tempMatrix.m21 = sinf(angle);		tempMatrix.m22 = cosf(angle);
	tempMatrix.dx = 0;					tempMatrix.dy = 0;

	return tempMatrix;
}

D2D_MATRIX_3X2_F GetScaleMatrix(float x, float y)
{
	D2D_MATRIX_3X2_F tempMatrix;
	tempMatrix.m11 = x;		tempMatrix.m12 = 0;
	tempMatrix.m21 = 0;		tempMatrix.m22 = y;
	tempMatrix.dx = 0;		tempMatrix.dy = 0;

	return tempMatrix;
}

D2D1_POINT_2F GetTransform(D2D1_POINT_2F& source, Transform transform)
{
	D2D1_POINT_2F tempPoint = source;

	D2D_MATRIX_3X2_F rotate = GetRotateMatrix(transform.Angle);
	D2D_MATRIX_3X2_F scale = GetScaleMatrix(transform.Scale.x, transform.Scale.y);
	D2D_MATRIX_3X2_F translate = GetTranslateMatrix(transform.Position.x, transform.Position.y);

	tempPoint = tempPoint * rotate;
	tempPoint = tempPoint * scale;
	tempPoint = tempPoint * translate;

	return tempPoint;
}

D2D1_POINT_2F operator*(D2D1_POINT_2F& pt, D2D_MATRIX_3X2_F& matrix)
{
	D2D1_POINT_2F tempPoint;
	tempPoint.x = pt.x * matrix.m11 + pt.y * matrix.m21 + matrix.dx;
	tempPoint.y = pt.y * matrix.m12 + pt.y * matrix.m22 + matrix.dy;

	return tempPoint;
}

D2D1_POINT_2F operator+(D2D1_POINT_2F& pt1, D2D1_POINT_2F& pt2)
{
	D2D1_POINT_2F tempPoint;
	tempPoint.x = pt1.x + pt2.x;
	tempPoint.y = pt1.y + pt2.y;

	return tempPoint;
}

D2D1_POINT_2F operator/(D2D1_POINT_2F& pt, float value)
{
	D2D1_POINT_2F tempPoint;
	tempPoint.x = pt.x / value;
	tempPoint.y = pt.y / value;

	return tempPoint;
}
