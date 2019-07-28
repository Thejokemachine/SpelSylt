#include "SpelSylt/SpelSyltPCH.h"
#include "FullScreenPass.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

SpelSylt::FullScreenPass::FullScreenPass()
{
	myVertices[0] = { {0.f,0.f}, {0.f,1.f} }; // Top Left
	myVertices[1] = { {1.f,0.f}, {1.f,1.f} }; // Top Right
	myVertices[2] = { {1.f,1.f}, {1.f,0.f} }; // Bottom Right
	myVertices[3] = { {0.f,0.f}, {0.f,1.f} }; // Top Left
	myVertices[4] = { {1.f,1.f}, {1.f,0.f} }; // Bottom Right
	myVertices[5] = { {0.f,1.f}, {0.f,0.f} }; // Bottom Left
}

void SpelSylt::FullScreenPass::RunPass(sf::RenderTarget & aTarget, const std::vector<const sf::Texture*>& aGBuffer)
{
	sf::View prevView = aTarget.getView();

	aTarget.setView(sf::View(sf::FloatRect(0.f, 0.f, 1.f, 1.f)));

	RunPassImpl(aTarget, aGBuffer);

	aTarget.setView(prevView);
}

void SpelSylt::FullScreenPass::RenderOnTargetWithShader(sf::RenderTarget & aTarget, const sf::Shader & aShader)
{
	aTarget.draw(&myVertices[0], 6, sf::PrimitiveType::Triangles, &aShader);
}
