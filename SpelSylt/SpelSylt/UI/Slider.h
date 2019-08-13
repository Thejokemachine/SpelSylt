#pragma once
#include "SpelSylt/UI/Panel.h"
#include "SpelSylt/tinyxml2.h"

namespace UI
{
	class Slider : public Panel
	{
	public:
		Slider(UILayout& aLayout, const Panel* aParent, tinyxml2::XMLElement& aElement);
		virtual ~Slider() = default;

		float GetValue() const;

		virtual void onUpdate(const float dt);
		virtual void onHover() override;
		virtual void onLayout() override;

	private:

		float myValue;
		bool myIsVertical;
		Panel* myCursor = nullptr;
	};
}