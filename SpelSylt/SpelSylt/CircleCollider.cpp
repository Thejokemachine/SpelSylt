#include "CircleCollider.h"

void CCircleCollider::SetRadius(float aRadius)
{
	myRadius = aRadius;
}

bool CCircleCollider::IsColliding(const CCircleCollider & aCircleCollider) const
{
	return CircleVsCircle(*this, aCircleCollider);
}

bool CCircleCollider::IsColliding(const CRectangleCollider & aRectangleCollider) const
{
	return CircleVsRectangle(*this, aRectangleCollider);
}

bool CCircleCollider::IsColliding(const CPointCollider & aPointCollider) const
{
	return CircleVsPoint(*this, aPointCollider);
}

sf::Vector2f CCircleCollider::GetSize() const
{
	return sf::Vector2f(getScale().x * 2.f * myRadius, getScale().y * 2.f * myRadius);
}
