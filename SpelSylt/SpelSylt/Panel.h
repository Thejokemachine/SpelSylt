#pragma once

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Drawable.hpp"

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
	HCenter = 32,
	VCenter = 64
};

class Panel : private sf::FloatRect, public sf::Drawable
{
	friend class UILayout;

public:
	Panel(const Panel* aParent, const std::string& aName, float x, float y, float aWidth, float aHeight, unsigned char aDockFlags);
	virtual ~Panel() = default;

	float GetX() const { return left; }
	float GetY() const { return top; }
	float GetWidth() const { return width; }
	float GetHeight() const { return height; }

	void SetImage(const std::string& aImage);
		
	void AddPanel(std::shared_ptr<Panel> aPanel);

	void ForEachChild(std::function<void(Panel& panel)> aFunction);

	void Update(const float dt);
	virtual void onUpdate(const float dt) {}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void onDraw(sf::RenderTarget& aTarget) const {}

private:

	std::vector<std::shared_ptr<Panel>> myChildren;

	const std::string myName;
	const Panel* myParent;
	const unsigned char myDockFlags;
	sf::Texture myTexture;
};