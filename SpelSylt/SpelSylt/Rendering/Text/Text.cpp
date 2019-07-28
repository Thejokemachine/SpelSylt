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
	setFont(*FontAsset);
}

//------------------------------------------------------------------

// void SpelSylt::CText::draw(sf::RenderTarget& InTarget, sf::RenderStates InStates) const
// {
// 	if (FontAsset && FontAsset->GetLoadStatus() == ELoadRequestStatus::Done)
// 	{
// 		sf::Text text;
// // 		text.setOutlineColor(getOutlineColor());
// // 		text.setOutlineThickness(getOutlineThickness());
// // 		text.setCharacterSize(getCharacterSize());
// // 		text.setLetterSpacing(getLetterSpacing());
// // 		text.setFillColor(getFillColor());
// // 		text.setScale(getScale());
// // 		text.setLineSpacing(getLineSpacing());
// // 		text.setStyle(getStyle());
// // 		text.setFont(*FontAsset);
// // 		text.setString(getString());
// // 
// // 		text.setPosition(getPosition());
// // 		//text.setOrigin(getOrigin());
// // 		text.setRotation(getRotation());
// 
// 		text.setString("hej värld");
// 		text.setPosition({ 0,0 });
// 		text.setFont(*FontAsset);
// 
// 		InTarget.draw(text, InStates);
// 	}
// }

//------------------------------------------------------------------