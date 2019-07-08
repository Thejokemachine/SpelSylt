#pragma once
#include "SFML/Graphics/Font.hpp"

#include <unordered_map>

class CFontBank
{
public:
	CFontBank();
	~CFontBank() = default;

	const sf::Font* GetFont(const std::string& aFontName) const;

private:
	std::unordered_map<std::string, sf::Font> myFonts;
};