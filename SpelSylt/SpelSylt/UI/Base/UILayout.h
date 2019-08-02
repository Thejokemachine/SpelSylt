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

namespace SpelSylt
{
	class CAssetManager;
	class IInputEventGetter;
	struct SGameContext;
}

namespace UI
{
	class Panel;
	class Button;
	class Label;
	class List;

	class UILayout
	{
	public:
		UILayout(float aWidth, float aHeight, const std::string& aLayoutXML, SpelSylt::CAssetManager& aAssetManager, SpelSylt::IInputEventGetter& aInputManager);
		virtual ~UILayout() = default;

		void Update(SS::SGameContext& InGameContext);
		void Render(sf::RenderTarget& aRenderTarget);
		void Resize(int aWidth, int aHeight);

		Panel* GetPanel(const std::string& aName);
		Button* GetButton(const std::string& aName);
		Label* GetLabel(const std::string& aName);
		List* GetList(const std::string& aName);

		float GetWidth() const;
		float GetHeight() const;

		SpelSylt::CAssetManager& GetFontBank() { return myAssetManager; }
		SpelSylt::IInputEventGetter& GetInputManager() { return myInputManager; }

	private:
		//Temp fix!
		SpelSylt::CAssetManager& myAssetManager;

		SpelSylt::IInputEventGetter& myInputManager;

		float evaluateExpression(const std::string& aAttributeBlock);

		SpelSylt::CDebugDrawer myDrawer;
		std::unique_ptr<Panel> myRootPanel;
		tinyxml2::XMLDocument myDocument;
	};
}