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
	//본인과 충돌 대상의 Active가 모두 켜져있으면 체크
	if (m_Active && p_target->m_Active)
	{
		//충돌 검사 대상이 BoxCollider면
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

		////CircleCollider면
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
