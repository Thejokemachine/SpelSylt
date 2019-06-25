#pragma once
#include <vector>
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RenderTexture.hpp"

namespace sf
{
	class Renderable;
	class RenderTexture;
}

class CRenderer
{
	friend class CMainSingleton;

public:
	CRenderer();

	struct SRenderCommand
	{
		sf::Drawable* myDrawable;
		short myLayer;
	};

	void SetDimensions(unsigned int aW, unsigned int aH);


	template<typename T>
	void PushRenderCommand(const T& aDrawable, short aLayer);

	sf::Sprite RunRendering();
	void Clear();

private:

	sf::RenderTexture myRenderTexture;
	std::vector<SRenderCommand> myRenderCommands;
};

template<typename T>
inline void CRenderer::PushRenderCommand(const T& aDrawable, short aLayer)
{
	SRenderCommand rc;
	rc.myDrawable = new T(aDrawable);
	rc.myLayer = aLayer;

	myRenderCommands.push_back(rc);
}
