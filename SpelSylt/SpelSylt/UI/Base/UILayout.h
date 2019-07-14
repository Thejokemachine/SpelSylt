#pragma once

#include <vector>
#include <memory>

#include "SpelSylt/Debugging/Rendering/DebugDrawer.h"
#include "SpelSylt/tinyxml2.h"

namespace sf
{
	class RenderTarget;
}

namespace tinyxml2
{
	class XMLElement;
	class XMLDocument;
}

class IInputEventGetter;
class CFontBank;

namespace UI
{
	class Panel;
	class Button;
	class Label;

	class UILayout
	{
	public:
		UILayout(float aWidth, float aHeight, CFontBank& aFontBank, const std::string& aLayoutXML);
		virtual ~UILayout() = default;

		void Update(IInputEventGetter* aInputManager);
		void Render(sf::RenderTarget& aRenderTarget);
		void Resize(int aWidth, int aHeight);

		Panel* GetPanel(const std::string& aName);
		Button* GetButton(const std::string& aName);
		Label* GetLabel(const std::string& aName);

		CFontBank& GetFontBank() { return myFontBank; }

	private:

		void addChildren(Panel& aParent, tinyxml2::XMLElement* aElement);

		float evaluateExpression(const std::string& aAttributeBlock);

		CDebugDrawer myDrawer;
		std::unique_ptr<Panel> myRootPanel;
		tinyxml2::XMLDocument myDocument;

		CFontBank& myFontBank;
	};
}