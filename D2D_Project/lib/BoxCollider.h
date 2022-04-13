#pragma once

class BoxCollider : public Collision
{
public:
	BoxCollider(Object* parent = nullptr);

public:
	virtual void CheckCollision(Collision* p_target);
	virtual void Draw();
};

