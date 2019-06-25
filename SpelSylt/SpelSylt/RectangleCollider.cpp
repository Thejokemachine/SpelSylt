#include "RectangleCollider.h"

void CRectangleCollider::SetDimensions(const sf::Vector2f & aDimensions)
{
	myDimensions = aDimensions;
}

sf::Vector2f CRectangleCollider::GetDimensions()
{
	return myDimensions;
}

bool CRectangleCollider::IsColliding(const CCircleCollider & aCircleCollider) const
{
	return CircleVsRectangle(aCircleCollider, *this);
}

bool CRectangleCollider::IsColliding(const CRectangleCollider & aRectangleCollider) const
{
	return RectangleVsRectangle(*this, aRectangleCollider);
}

bool CRectangleCollider::IsColliding(const CPointCollider & aPointCollider) const
{
	return PointVsRectangle(aPointCollider, *this);
}

sf::Vector2f CRectangleCollider::GetSize() const
{
	return sf::Vector2f(getScale().x * myDimensions.x, getScale().y * myDimensions.y);
}
