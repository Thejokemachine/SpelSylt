#pragma once
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/Sprite.hpp"

#include <vector>

namespace AnimationEditor {

	class SimpleAnimation : public sf::Sprite
	{
	public:
		SimpleAnimation();
		~SimpleAnimation();

		void addFrame(const std::string& texturePath, float duration);
		void tick(float dt);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		
		struct SFrame 
		{
			float duration;
			sf::Texture texture;
		};

		std::vector<SFrame> frames;
		short cursor = 0;
		float time = 0.f;
	};
}