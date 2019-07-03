#pragma once

#include <vector>

#include "Panel.h"
#include "DebugDrawer.h"
#include "InputManager.h"

namespace sf
{
	class RenderTarget;
}

namespace tinyxml2
{
	class XMLElement;
}

class UILayout
{
public:
	UILayout(float aWidth, float aHeight);
	virtual ~UILayout() = default;

	void Update(CInputManager* aInputManager);
	void Render(sf::RenderTarget& aRenderTarget);

private:
	
	unsigned char evaluateDockingFlags(const std::string& aBlock);
	void addChildren(Panel& aParent, tinyxml2::XMLElement* aElement);

	CDebugDrawer myDrawer;
	Panel myRootPanel;
};