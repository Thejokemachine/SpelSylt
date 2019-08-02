#pragma once
#include "SpelSylt/UI/Panel.h"
#include <vector>
#include "SpelSylt/tinyxml2.h"

namespace UI
{
	class List : public Panel
	{
	public:
		List(UILayout& aLayout, const Panel* aParent, tinyxml2::XMLElement& aElement);
		virtual ~List() = default;

		Panel* AddItem(const std::string& aItemTemplateName);

		virtual void onUpdate(const float dt);
		virtual void onHover() override;
		virtual void onLayout() override;
		virtual void onDraw(sf::RenderTarget& aTarget) const;

	private:
		std::vector<std::shared_ptr<Panel>> myItems;
		std::unordered_map<std::string, tinyxml2::XMLElement*> myItemTemplates;

		float myMargin = 0.f;
		float myScroll = 0.f;
		float myMaxScroll = 0.f;
	};
}