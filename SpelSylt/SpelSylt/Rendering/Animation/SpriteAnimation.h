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

	enum class EAnimationPlayType
	{
		OneShot,
		Looping,
	};

	class CSpriteAnimation
		: public sf::Sprite
	{
	public:
		CSpriteAnimation();

		void operator=(const CSpriteAnimation& InRHS);
		void operator=(const SAnimationAsset& InRHS);

		void SetPlayType(EAnimationPlayType InPlayType);
		bool IsFinished() const;
		void Restart();

		void setTexture(const sf::Texture& texture, bool resetRect /* = false */) = delete;

		sf::Vector2u GetFrameSize() const;

		void Tick(float InDeltaTime);
		virtual void draw(sf::RenderTarget& InTarget, sf::RenderStates InStates) const override;
	private:
		void LoadData();
		void IncrementFrame();

		float TimeUntilNextFrame;
		unsigned int CurrentFrame;
		unsigned int MaxFrames;

		EAnimationPlayType PlayType;
		const SAnimationAsset* AnimationAsset;

		bool DataLoaded : 1;
		bool FinishedPlaying : 1;
	};
}

namespace SS = SpelSylt;