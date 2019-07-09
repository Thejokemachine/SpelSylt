#pragma once
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Transformable.hpp"

class CCircleCollider;
class CRectangleCollider;
class CPointCollider;

class CCollider : public sf::Transformable
{
public:

	enum class EColliderType : short
	{
		Circle,
		Rectangle,
		Point,
		Count
	};

	CCollider()
		: myType(EColliderType::Count)
	{
	}
	
	virtual bool IsColliding(const CCollider& aCollider) const = 0;

	virtual bool IsColliding(const CCircleCollider& aCircleCollider) const = 0;
	virtual bool IsColliding(const CRectangleCollider& aRectangleCollider) const = 0;
	virtual bool IsColliding(const CPointCollider& aPointCollider) const = 0;

	virtual sf::Vector2f GetSize() const = 0;

	EColliderType GetType() const { return myType; }

protected:

	static bool CircleVsCircle(const CCircleCollider& aCollider1, const CCircleCollider& aCollider2);
	static bool CircleVsRectangle(const CCircleCollider& aCollider1, const CRectangleCollider& aCollider2);
	static bool CircleVsPoint(const CCircleCollider& aCollider1, const CPointCollider& aCollider2);

	static bool PointVsPoint(const CPointCollider& aCollider1, const CPointCollider& aCollider2);
	static bool PointVsRectangle(const CPointCollider& aCollider1, const CRectangleCollider& aCollider2);

	static bool RectangleVsRectangle(const CRectangleCollider& aCollider1, const CRectangleCollider& aCollider2);

	EColliderType myType;
};