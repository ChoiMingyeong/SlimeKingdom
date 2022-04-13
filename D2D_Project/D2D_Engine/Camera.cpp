#include "pch.h"
#include "Camera.h"

Camera::Camera(Object* parent)
	:m_MyScene(MySceneManager->GetNowScene())
{
	if (parent != nullptr)
	{
		m_Parent = parent;
	}
}

Camera::~Camera()
{

}

Transform Camera::GetCameraTransform(Transform& target)
{
	Transform resultTransform;

	resultTransform = m_Transform - target;

	return resultTransform;
}
