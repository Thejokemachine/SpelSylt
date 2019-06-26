#pragma once

#include "SFML/Graphics/Rect.hpp"

#include <vector>
#include <memory>
#include <functional>

enum DockFlag : unsigned char
{
	None = 0,
	Left = 1,
	Right = 2,
	Top = 4,
	Bottom = 8,
	Center = 16,
};

class Panel : private sf::FloatRect
{
	friend class UILayout;

public:
	Panel(const Panel* aParent, const std::string& aName, float x, float y, float aWidth, float aHeight, unsigned char aDockFlags);
	virtual ~Panel() = default;

	float GetX() const { return left; }
	float GetY() const { return top; }
	float GetWidth() const { return width; }
	float GetHeight() const { return height; }

	void AddPanel(std::shared_ptr<Panel> aPanel);

	void ForEachChild(std::function<void(Panel& panel)> aFunction);

	void Update(const float dt);
	virtual void onUpdate(const float dt) {};

private:

	std::vector<std::shared_ptr<Panel>> myChildren;

	const std::string myName;
	const Panel* myParent;
	const unsigned char myDockFlags;
};