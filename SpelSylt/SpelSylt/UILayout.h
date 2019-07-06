#pragma once

#include <vector>

#include "Panel.h"
#include "DebugDrawer.h"

namespace sf
{
	class RenderTarget;
}

namespace tinyxml2
{
	class XMLElement;
}

class IInputEventGetter;

namespace UI
{
	class Button;

	class UILayout
	{
	public:
		UILayout(float aWidth, float aHeight);
		virtual ~UILayout() = default;

		void Update(IInputEventGetter* aInputManager);
		void Render(sf::RenderTarget& aRenderTarget);

		Panel* GetPanel(const std::string& aName);
		Button* GetButton(const std::string& aName);

	private:

		void addChildren(Panel& aParent, tinyxml2::XMLElement* aElement);

		CDebugDrawer myDrawer;
		Panel myRootPanel;
	};
}