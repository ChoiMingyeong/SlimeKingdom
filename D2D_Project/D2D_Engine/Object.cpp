#include "pch.h"
#include "Object.h"

Object::Object()
	:m_Active(true), m_Visible(true)
{
	m_Transform = Transform();

	m_Parent = this;
}

Transform Object::GetTransfrom()
{
	if (m_Parent == this) return m_Transform;
	return m_Parent->m_Transform + m_Transform;
}