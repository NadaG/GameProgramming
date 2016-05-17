#include "colliderclass.h"

Collider::Collider()
{
	m_center = { 0.0f, 0.0f, 0.0f };
	m_size = { 1.0f, 1.0f, 1.0f };
	m_radius = 1.0f;
}

Collider::Collider(const COLLIDER_TYPE& collider_type)
{
	m_type = collider_type;
	m_center = { 0.0f, 0.0f, 0.0f };
	m_size = { 1.0f, 1.0f, 1.0f };
	m_radius = 1.0f;
}

Collider::Collider(const Collider&)
{
}

Collider::~Collider()
{
}

const D3DXVECTOR3& Collider::GetCenter()
{
	return m_center;
}

const D3DXVECTOR3& Collider::GetSize()
{
	return m_size;
}

const float& Collider::GetRadius()
{
	return m_radius;
}

const COLLIDER_TYPE& Collider::GetType()
{
	return m_type;
}

void Collider::SetCenter(const D3DXVECTOR3& center)
{
	m_center = center;
}

void Collider::SetSize(const D3DXVECTOR3& size)
{
	m_size = size;
}

void Collider::SetSize(const float& radius)
{
	m_radius = radius;
}