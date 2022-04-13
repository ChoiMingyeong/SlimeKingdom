#pragma once

class Scene;

class GameObject : public Object, public Observer
{
public:
	GameObject(Object* parent = nullptr);
	virtual ~GameObject();

public:
	Scene* m_MyScene;

	Collision* m_pCollider;
	Renderer* m_pRenderer;
	Animation* m_pAnimation;

public:
	virtual void Update();
	virtual void CheckCollision(GameObject* p_target);
	virtual void Draw();

	void SetBoxCollider();
	void SetCircleCollider();

	void ResetHit();
	bool IsHit(GameObject* p_target);
	void SetSprite(Sprite* p_sprite);
	void SetAnimation(Animation* p_anim);
};

