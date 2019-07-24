#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/Rendering/Text/Text.h"
#include "SpelSylt/FileHandling/Asset/AssetTypes/FontAsset.h"

#include <SFML/Graphics/RenderTarget.hpp>

using namespace SpelSylt;

//------------------------------------------------------------------

CText::CText()
	: FontAsset(nullptr)
{
}

//------------------------------------------------------------------

void CText::SetFontAsset(const SFontAsset& InAsset)
{
	FontAsset = &InAsset;
}

//------------------------------------------------------------------

void SpelSylt::CText::draw(sf::RenderTarget& InTarget, sf::RenderStates InStates) const
{
	if (FontAsset->GetLoadStatus() == ELoadRequestStatus::Done)
	{
		InTarget.draw(*this, InStates);
	}
}

//------------------------------------------------------------------