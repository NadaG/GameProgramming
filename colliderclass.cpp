#include "colliderclass.h"

Collider::Collider()
:m_center(0.0f, 0.0f, 0.0f),
m_size(1.0f, 1.0f, 1.0f),
m_rotation(0.0f,0.0f,0.0f),
m_radius(1.0f)
{
}

Collider::Collider(const COLLIDER_TYPE& collider_type)
:m_type(collider_type),
m_center(0.0f, 0.0f, 0.0f),
m_size(1.0f, 1.0f, 1.0f),
m_rotation(0.0f, 0.0f, 0.0f),
m_radius(1.0f)
{
}

Collider::Collider(const Collider&)
{
}

Collider::~Collider()
{
}

const Vector3f& Collider::GetCenter()
{
	return m_center;
}

const Vector3f& Collider::GetSize()
{
	return m_size;
}

const float& Collider::GetRadius()
{
	return m_radius;
}

const Vector3f& Collider::GetRotation()
{
	return m_rotation;
}

const COLLIDER_TYPE& Collider::GetType()
{
	return m_type;
}

void Collider::SetCenter(const Vector3f& center)
{
	m_center = center;
}

void Collider::SetSize(const Vector3f& size)
{
	m_size = size;
}

void Collider::SetRadius(const float& radius)
{
	m_radius = radius;
}

void Collider::SetRotation(const Vector3f& rotation)
{
	m_rotation = rotation;
}