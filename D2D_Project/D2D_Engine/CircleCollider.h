#pragma once

class CircleCollider : public Collision
{
public:
	CircleCollider(Object* parent = nullptr);

public:
	virtual void CheckCollision(Collision* p_target);
	virtual void Draw();
};

