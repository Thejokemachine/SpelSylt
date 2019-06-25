#pragma once
#include "Collider.h"

class CCircleCollider : public CCollider
{
	friend class CCollider;

public:
	CCircleCollider() { myType = CCollider::EColliderType::Circle; };

	void SetRadius(float aRadius);
	virtual bool IsColliding(const CCollider& aCollider) const override { return aCollider.IsColliding(*this); }

	virtual bool IsColliding(const CCircleCollider& aCircleCollider) const override;
	virtual bool IsColliding(const CRectangleCollider& aRectangleCollider) const override;
	virtual bool IsColliding(const CPointCollider& aPointCollider) const override;

	virtual sf::Vector2f GetSize() const override;

private:

	float myRadius;
};