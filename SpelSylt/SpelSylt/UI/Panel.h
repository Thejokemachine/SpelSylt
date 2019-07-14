#pragma once

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Drawable.hpp"

#include <vector>
#include <memory>
#include <functional>

namespace tinyxml2 {
	class XMLElement;
}

namespace UI
{

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

	class UILayout;

	class Panel : private sf::FloatRect, public sf::Drawable
	{
		friend UILayout;

	public:
		Panel(UILayout& aLayout, const Panel* aParent, const std::string& aName, float x, float y, float aWidth, float aHeight, unsigned char aDockFlags, tinyxml2::XMLElement& aElement);
		Panel(UILayout& aLayout, const Panel* aParent, tinyxml2::XMLElement& aElement);
		virtual ~Panel() = default;

		// Getters -------------------------------------
		float GetX() const { return left; }
		float GetY() const { return top; }
		virtual float GetWidth() const { return width; }
		virtual float GetHeight() const { return height; }
		Panel* GetPanel(const std::string& aName);
		// ---------------------------------------------

		// Setters
		void SetImage(const std::string& aImage);
		void SetColor(const sf::Color& aColor);
		void SetBounds(float x, float y, float width, float height);
		// ---------------------------------------------

		void AddPanel(std::shared_ptr<Panel> aPanel);

		void Layout();
		virtual void onLayout() {};

		void ForEachChild(std::function<void(Panel& panel)> aFunction);

		void Update(const float dt);
		virtual void onUpdate(const float dt) {}

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void onDraw(sf::RenderTarget& aTarget) const {}

	protected:

		void setDirty();

		float evaluateExpression(const std::string& aAttributeBlock);

		UILayout& myLayout;
		tinyxml2::XMLElement& myXMLElement;

	private:

		std::vector<std::shared_ptr<Panel>> myChildren;

		std::string myName;
		const Panel* myParent;
		unsigned char myDockFlags;
		sf::Texture myTexture;
		sf::Color myColor;
		float myX;
		float myY;

		bool myIsDirty = false;
	};

}