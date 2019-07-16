#pragma once
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/Sprite.hpp"

#include <vector>

namespace AnimationEditor {

	class SimpleAnimation : public sf::Transformable, public sf::Drawable
	{
	public:
		SimpleAnimation();
		~SimpleAnimation();

		void setMaxSize(float width, float height);

		void addFrame(const std::string& texturePath, float duration);
		void tick(float dt);

		void setGlobalSpeed(float speed);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		
		struct SFrame 
		{
			float duration;
			sf::Texture texture;
		};

		float maxWidth = -1.f;
		float maxHeight = -1.f;

		std::vector<SFrame> frames;
		short cursor = 0;
		float time = 0.f;
	};
}