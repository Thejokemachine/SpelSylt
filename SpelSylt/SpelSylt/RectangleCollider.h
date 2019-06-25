#pragma once
#include "Collider.h"

class CRectangleCollider : public CCollider
{
	friend class CCollider;

public:
	CRectangleCollider() { myType = CCollider::EColliderType::Rectangle; };

	void SetDimensions(const sf::Vector2f& aDimensions);
	sf::Vector2f GetDimensions();
	virtual bool IsColliding(const CCollider& aCollider) const override { return aCollider.IsColliding(*this); }

	virtual bool IsColliding(const CCircleCollider& aCircleCollider) const;
	virtual bool IsColliding(const CRectangleCollider& aRectangleCollider) const;
	virtual bool IsColliding(const CPointCollider& aPointCollider) const;

	virtual sf::Vector2f GetSize() const override;

private:

	sf::Vector2f myDimensions;
};