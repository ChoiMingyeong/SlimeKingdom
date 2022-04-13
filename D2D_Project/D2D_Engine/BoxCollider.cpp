#include "pch.h"
#include "BoxCollider.h"

BoxCollider::BoxCollider(Object* parent)
{
	if (parent != nullptr)
	{
		m_Parent = parent;
	}
}

void BoxCollider::CheckCollision(Collision* p_target)
{
	//���ΰ� �浹 ����� Active�� ��� ���������� üũ
	if (m_Active && p_target->m_Active)
	{
		//�浹 �˻� ����� BoxCollider��
		if (dynamic_cast<BoxCollider*>(p_target) != nullptr)
		{
			BoxCollider* pTarget = dynamic_cast<BoxCollider*>(p_target);

			PT4_Rect myBB = GetBoundingBox();
			PT4_Rect targetBB = pTarget->GetBoundingBox();

			if (myBB.pt[0].x < targetBB.pt[2].x
				&& targetBB.pt[0].x < myBB.pt[2].x)
			{
				if (myBB.pt[0].y < targetBB.pt[2].y
					&& targetBB.pt[0].y < myBB.pt[2].y)
				{
					m_HitObjects.push_back(pTarget->m_Parent);
					pTarget->m_HitObjects.push_back(this->m_Parent);
				}
			}
		}

		////CircleCollider��
		//if (dynamic_cast<CircleCollider*>(this) != nullptr)
		//{
		//	CircleCollider* pTempCircleCollider = dynamic_cast<CircleCollider*>(this);
		//	pTempCircleCollider->CheckCollision(p_target);
		//}
	}
}

void BoxCollider::Draw()
{
	if (m_Active && m_Visible)
	{
		MyEngine->SetTransform((m_Parent->GetTransfrom() + m_Transform).GetSR());
		D2D1_POINT_2F drawPoint = { m_Parent->GetTransfrom().Position.x, m_Parent->GetTransfrom().Position.y };
		MyEngine->DrawRectangle(drawPoint, m_Size.m_Width, m_Size.m_Height, CollisionColor);
		MyEngine->SetTransform(D2D1::Matrix3x2F::Identity());
	}
}
