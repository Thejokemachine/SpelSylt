#include "SpelSylt/SpelSyltPCH.h"
#include "SpelSylt/FileHandling/Banks/FontBank.h"
#include "SpelSylt/FileHandling/DirectoryHelpers.h"

CFontBank::CFontBank()
{
	SDirectoryHelpers::VisitDirectory(
		"UI/Fonts",
		[&](const FFile & InFile) {
		std::string alias = InFile.path().stem().string();
		std::string fileName = InFile.path().string();

		myFonts[alias].loadFromFile(fileName);
	});
}

const sf::Font* CFontBank::GetFont(const std::string& aFontName) const
{
	if (myFonts.find(aFontName) != myFonts.end())
		return &myFonts.at(aFontName);

	return nullptr;
}