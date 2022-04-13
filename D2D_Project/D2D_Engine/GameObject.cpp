#include "pch.h"
#include "GameObject.h"

GameObject::GameObject(Object* parent)
	:m_MyScene(MySceneManager->GetNowScene())
{
	if (parent != nullptr)
	{
		m_Parent = parent;
	}
	m_pRenderer = new Renderer(this);
	SetBoxCollider();

	m_pAnimation = nullptr;

	m_MyScene->m_pGameObjectManager->ResisterObserver(this);
}

GameObject::~GameObject()
{
	if (m_pCollider != nullptr)
	{
		delete m_pCollider;
	}
	m_MyScene->m_pGameObjectManager->RemoveObserver(this);
}

void GameObject::Update()
{
	if (m_pAnimation != nullptr)
	{
		m_pAnimation->Update();
		m_pRenderer->SetSprite(m_pAnimation->GetNowSprite());
	}
}

void GameObject::CheckCollision(GameObject* p_target)
{
	m_pCollider->CheckCollision(p_target->m_pCollider);
}

void GameObject::Draw()
{
	if (m_Active && m_Visible)
	{
		Transform originTransfrom = m_Transform;

		m_Transform = MySceneManager->GetNowScene()->m_pCamera->GetCameraTransform(m_Transform);
		m_pRenderer->Draw();
		m_pCollider->Draw();

		m_Transform = originTransfrom;
	}
}

void GameObject::SetBoxCollider()
{
	if (m_pCollider != nullptr)
	{
		delete m_pCollider;
	}
	m_pCollider = new BoxCollider(this);
	m_pCollider->SetValue(m_pRenderer->m_Size);
}

void GameObject::SetCircleCollider()
{
	if (m_pCollider != nullptr)
	{
		delete m_pCollider;
	}
	m_pCollider = new CircleCollider(this);
	m_pCollider->SetValue(m_pRenderer->m_Size);
}

void GameObject::ResetHit()
{
	m_pCollider->ResetHit();
}

bool GameObject::IsHit(GameObject* target)
{
	for (int i = 0; i < m_pCollider->m_HitObjects.size(); i++)
	{
		if (m_pCollider->m_HitObjects[i] == target)
		{
			return true;
		}
	}
	return false;
}

void GameObject::SetSprite(Sprite* p_sprite)
{
	if (m_pRenderer == nullptr)
	{
		m_pRenderer = new Renderer(this);
	}
	m_pRenderer->SetSprite(p_sprite);

	if (m_pCollider != nullptr)
	{
		float width = m_pRenderer->m_pSprite->m_SpriteRect.right - m_pRenderer->m_pSprite->m_SpriteRect.left;
		float height = m_pRenderer->m_pSprite->m_SpriteRect.bottom - m_pRenderer->m_pSprite->m_SpriteRect.top;

		m_pCollider->m_Size.m_Width = width;
		m_pCollider->m_Size.m_Height = height;
	}
}

void GameObject::SetAnimation(Animation* p_anim)
{
	if (m_pAnimation == nullptr)
	{
		m_pAnimation = new Animation(p_anim->m_pSprites);
	}
	m_pAnimation = p_anim;
	SetSprite(m_pAnimation->GetNowSprite());
}
