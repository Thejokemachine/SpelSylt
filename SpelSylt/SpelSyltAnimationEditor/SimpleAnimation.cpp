#include "SimpleAnimation.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

AnimationEditor::SimpleAnimation::SimpleAnimation()
{
}

AnimationEditor::SimpleAnimation::~SimpleAnimation()
{
}

void AnimationEditor::SimpleAnimation::addFrame(const std::string & texturePath, float duration)
{
	frames.emplace_back(SFrame());
	frames.back().texture.loadFromFile(texturePath);
	frames.back().duration = duration;
}

void AnimationEditor::SimpleAnimation::tick(float dt)
{
	time += dt;
	float frameTime = 0.f;
	for (size_t i = 0; i < frames.size(); ++i)
	{
		auto& frame = frames[i];
		frameTime += frame.duration;
		if (time <= frameTime)
		{
			cursor = (short)i;
			break;
		}
		else if (i == frames.size()-1)
		{
			cursor = 0;
			time -= frameTime;
		}
	}
}

void AnimationEditor::SimpleAnimation::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	sf::Sprite sprite;
	auto& currentFrame = frames[cursor];
	sprite.setPosition(getPosition());
	sprite.setOrigin(0.5f * currentFrame.texture.getSize().x, 0.5f * currentFrame.texture.getSize().y);
	sprite.setTexture(currentFrame.texture);
	target.draw(sprite, states);
}
