#pragma once

#include <vector>

#include "Panel.h"
#include "DebugDrawer.h"
#include "InputManager.h"

namespace sf
{
	class RenderTarget;
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

	CDebugDrawer myDrawer;
	Panel myRootPanel;
};