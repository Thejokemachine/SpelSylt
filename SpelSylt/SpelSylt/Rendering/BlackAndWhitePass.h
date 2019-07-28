#pragma once
#include "FullScreenPass.h"
#include "SpelSylt/Rendering/Shader/Shader.h"

namespace SpelSylt
{
	class CAssetManager;

	class BlackAndWhitePass : public FullScreenPass
	{
	public:
		BlackAndWhitePass(CAssetManager& InAssetManager);

	private:
		virtual void RunPassImpl(sf::RenderTarget& aTarget, const std::vector<const sf::Texture*>& aGBuffer) override;

		CShader myShader;
	};
}

namespace SS = SpelSylt;