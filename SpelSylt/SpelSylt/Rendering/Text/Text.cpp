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

void CText::SetString(const char* InString)
{
	TextString = InString;
}

//------------------------------------------------------------------

void CText::SetFontAsset(const SFontAsset& InAsset)
{
	FontAsset = &InAsset;
	sf::Text::setFont(*FontAsset);
}

//------------------------------------------------------------------

void SpelSylt::CText::draw(sf::RenderTarget& InTarget, sf::RenderStates InStates) const
{
	if (FontAsset->GetLoadStatus() == ELoadRequestStatus::Done)
	{
		sf::Text RenderText = *this;
		RenderText.setString(TextString.c_str());
		
		InTarget.draw(RenderText, InStates);
	}
}

//------------------------------------------------------------------