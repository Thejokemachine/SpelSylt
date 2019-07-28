#pragma once
#include <SFML/Graphics/Sprite.hpp>

namespace sf
{
	class Texture;
	class RenderTarget;
	class RenderStates;
}

namespace SpelSylt
{
	struct SAnimationAsset;

	class CSpriteAnimation
		: public sf::Sprite
	{
	public:
		CSpriteAnimation();

		void operator=(const CSpriteAnimation& InRHS);
		void operator=(const SAnimationAsset& InRHS);

		void setTexture(const sf::Texture& texture, bool resetRect /* = false */) = delete;

		void Tick(float InDeltaTime);
		virtual void draw(sf::RenderTarget& InTarget, sf::RenderStates InStates) const override;
	private:
		void LoadData();
		void IncrementFrame();

		float TimeUntilNextFrame;
		unsigned int CurrentFrame;
		unsigned int MaxFrames;

		const SAnimationAsset* AnimationAsset;

		bool DataLoaded : 1;
	};
}

namespace SS = SpelSylt;