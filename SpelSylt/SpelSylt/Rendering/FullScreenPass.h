#pragma once

#include <SFML/Graphics/Vertex.hpp>
#include <vector>

namespace sf
{
	class Texture;
	class Shader;
	class RenderTarget;;
}

namespace SpelSylt
{
	class FullScreenPass
	{
	public:
		FullScreenPass();

		void RunPass(sf::RenderTarget& aTarget, const std::vector<const sf::Texture*>& aGBuffer);

	protected:

		void RenderOnTargetWithShader(sf::RenderTarget& aTarget, const sf::Shader& aShader);

		virtual void RunPassImpl(sf::RenderTarget& aTarget, const std::vector<const sf::Texture*>& aGBuffer) {};

	private:
		sf::Vertex myVertices[6];
	};
}

namespace SS = SpelSylt;