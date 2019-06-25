#include "Collider.h"
#include "CommonMath.h"
#include "CircleCollider.h"
#include "RectangleCollider.h"
#include "PointCollider.h"

bool CCollider::CircleVsCircle(const CCircleCollider & aCollider1, const CCircleCollider & aCollider2)
{
	float distance = Math::Length2(aCollider1.getPosition() - aCollider2.getPosition());
	float maxDistance = (aCollider1.myRadius + aCollider2.myRadius) * (aCollider1.myRadius + aCollider2.myRadius);

	return distance < maxDistance;
}

bool CCollider::CircleVsRectangle(const CCircleCollider & aCollider1, const CRectangleCollider & aCollider2)
{
	sf::Vector2f clampedPos = aCollider1.getPosition();
	clampedPos.x = Math::Clamp(clampedPos.x, aCollider2.getPosition().x - aCollider2.myDimensions.x / 2.f, aCollider2.getPosition().x + aCollider2.myDimensions.x / 2.f);
	clampedPos.y = Math::Clamp(clampedPos.y, aCollider2.getPosition().y - aCollider2.myDimensions.y / 2.f, aCollider2.getPosition().y + aCollider2.myDimensions.y / 2.f);

	float distance = Math::Length2(clampedPos - aCollider1.getPosition());
	float maxDistance = aCollider1.myRadius * aCollider1.myRadius;

	return distance < maxDistance;
}

bool CCollider::CircleVsPoint(const CCircleCollider & aCollider1, const CPointCollider & aCollider2)
{
	float distance = Math::Length2(aCollider1.getPosition() - aCollider2.getPosition());

	return distance < aCollider1.myRadius * aCollider1.myRadius;
}

bool CCollider::PointVsPoint(const CPointCollider & aCollider1, const CPointCollider& aCollider2)
{
	return aCollider1.getPosition() == aCollider2.getPosition();
}

bool CCollider::PointVsRectangle(const CPointCollider & aCollider1, const CRectangleCollider & aCollider2)
{
	sf::Vector2f pos = aCollider1.getPosition();
	float left = aCollider2.getPosition().x - aCollider2.myDimensions.x / 2;
	float right = aCollider2.getPosition().x + aCollider2.myDimensions.x / 2;
	float top = aCollider2.getPosition().y - aCollider2.myDimensions.y / 2;
	float bottom = aCollider2.getPosition().y + aCollider2.myDimensions.y / 2;

	return (pos.x >= left && 
		pos.x <= right &&
		pos.y >= top &&
		pos.y <= bottom);
}

bool CCollider::RectangleVsRectangle(const CRectangleCollider & aCollider1, const CRectangleCollider & aCollider2)
{
	float left1 = aCollider1.getPosition().x - aCollider1.myDimensions.x / 2;
	float right1 = aCollider1.getPosition().x + aCollider1.myDimensions.x / 2;
	float top1 = aCollider1.getPosition().y - aCollider1.myDimensions.y / 2;
	float bottom1 = aCollider1.getPosition().y + aCollider1.myDimensions.y / 2;

	float left2 = aCollider2.getPosition().x - aCollider2.myDimensions.x / 2;
	float right2 = aCollider2.getPosition().x + aCollider2.myDimensions.x / 2;
	float top2 = aCollider2.getPosition().y - aCollider2.myDimensions.y / 2;
	float bottom2 = aCollider2.getPosition().y + aCollider2.myDimensions.y / 2;

	return (left1 <= right2 &&
		right1 >= left2 &&
		top1 <= bottom2 &&
		bottom1 >= top2);
}
