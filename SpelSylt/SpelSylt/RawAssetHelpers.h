#pragma once

struct SRawAsset;

namespace sf
{
	class Texture;
}

struct SRawAssetHelpers
{
public:
	static void ToTexture(SRawAsset& InAsset, sf::Texture& OutTexture);
};