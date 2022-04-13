#pragma once
class Camera : public Object
{
public:
	Camera(Object* parent = nullptr);
	virtual ~Camera();

public:
	Scene* m_MyScene;

public:
	virtual void Update() {};
	virtual void Draw() {};

	Transform GetCameraTransform(Transform& target);
};

