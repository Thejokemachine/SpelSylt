#include "Renderer.h"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderTexture.hpp"

CRenderer::CRenderer()
{
}

void CRenderer::SetDimensions(unsigned int aW, unsigned int aH)
{
	myRenderTexture.create(aW, aH);
}

sf::Sprite CRenderer::RunRendering()
{
	for (SRenderCommand& command : myRenderCommands)
	{
		myRenderTexture.draw(*command.myDrawable);
	}

	myRenderCommands.clear();

	myRenderTexture.display();

	sf::Sprite renderedImage;
	renderedImage.setTexture(myRenderTexture.getTexture());

	return std::move(renderedImage);
}

void CRenderer::Clear()
{
	myRenderTexture.clear();
}

