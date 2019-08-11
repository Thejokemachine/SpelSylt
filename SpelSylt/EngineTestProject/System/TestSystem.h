#pragma once
#include <SpelSylt/System/SystemInterface.h>

#include <SpelSylt/Rendering/Sprite/Sprite.h>

#include <SFML/System/Vector2.hpp>

namespace SpelSylt
{
	class CAssetManager;
	class CRenderQueue;
}

namespace testproj
{
	class CTestSystem final
		: public SS::ISystem
	{
	public:
		CTestSystem(SpelSylt::CAssetManager& InAssetManager);
		virtual void Tick(float InDT) override;
		virtual void Render(SpelSylt::CRenderQueue& InRenderQueue) override;
	private:
		SS::CSprite TestSystemSprite;
		sf::Vector2f Pos;
		bool DirRight;
	};

}