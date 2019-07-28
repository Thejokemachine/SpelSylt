#include "SpelSylt/SpelSyltPCH.h"
#include "BlackAndWhitePass.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "SpelSylt/Math/CommonMath.h"
#include "SpelSylt/FileHandling/Asset/AssetManager.h"

SpelSylt::BlackAndWhitePass::BlackAndWhitePass(CAssetManager& InAssetManager)
{
	myShader = InAssetManager.GetAsset<SS::SShaderAsset>("Shaders/Fullscreen/BlackAndWhite.frag", ELoadSettings::Async);
}

void SpelSylt::BlackAndWhitePass::RunPassImpl(sf::RenderTarget & aTarget, const std::vector<const sf::Texture*>& aGBuffer)
{
	sf::View prevView = aTarget.getView();

	aTarget.setView(sf::View(sf::FloatRect(0.f, 0.f, 1.f, 1.f)));

	const sf::Texture& albedo = *(aGBuffer[0]);

	static float intensity = 0.f;
	intensity += 0.25f;

	myShader.Get().setUniform("albedo", albedo);
	myShader.Get().setUniform("intensity", Math::Max(0.f, 5.f * sinf(intensity)));

	RenderOnTargetWithShader(aTarget, myShader.Get());

	aTarget.setView(prevView);
}
