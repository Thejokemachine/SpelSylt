#include "HeightMapToNormalMapConverter/NormalMapBuilder.h"

#include "HeightMapToNormalMapConverter/FileMutator.h"
#include "HeightMapToNormalMapConverter/MessagePrinter.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include <filesystem>

//------------------------------------------------------------------

CNormalMapBuilder::CNormalMapBuilder()
	: Count(0)
{
	ConversionShader.loadFromFile("ConverterShader.frag", sf::Shader::Type::Fragment);
	ConversionShader.setUniform("scale", 10.f);
}

//------------------------------------------------------------------

void CNormalMapBuilder::GenerateNMForEachHMInDirectory(const std::string& InHeightMapsDirectory)
{
	for (auto&& File : std::filesystem::directory_iterator(InHeightMapsDirectory))
	{
		const std::filesystem::path& Path = File.path();
		const std::filesystem::path PngExtension(".png");

		if (Path.extension() != PngExtension)
		{
			continue;
		}

		const std::string& FileName = Path.stem().string();

		if (FileName.find("_HM") == std::string::npos)
		{
			continue;
		}
		Count++;

		MessagePrinter::PrintNumberedMessage(Count, "Starting NM generation for " + Path.filename().string());
		GenerateNM(Path.string(), InHeightMapsDirectory);
	}
}

//------------------------------------------------------------------

void CNormalMapBuilder::GenerateNM(const std::string& InPathToHM, const std::string& InDirectory)
{
	sf::Texture Texture;
	if (!Texture.loadFromFile(InPathToHM))
	{
		MessagePrinter::PrintNumberedMessage(Count, "Failed to load " + InPathToHM);
		return;
	}

	sf::Sprite Sprite;
	Sprite.setTexture(Texture);

	sf::RenderTexture CreatedTexture;
	CreatedTexture.create(Texture.getSize().x, Texture.getSize().y);
	CreatedTexture.clear();
	CreatedTexture.draw(Sprite, &ConversionShader);

	std::filesystem::path PathToHeightMap = InPathToHM;

	std::string OutPath = InDirectory;
	OutPath += FileMutator::GetFileNameWithoutSuffix(PathToHeightMap.stem().string());
	OutPath += "_NM.png";
	sf::Image CreatedImage = CreatedTexture.getTexture().copyToImage();
	CreatedImage.flipVertically();

	if (!CreatedImage.saveToFile(OutPath))
	{
		MessagePrinter::PrintNumberedMessage(Count, "Failed to save " + OutPath);
		return;
	}

	std::filesystem::path SavedFileAsPath(OutPath);
	MessagePrinter::PrintNumberedMessage(Count, "Generated NM from " + PathToHeightMap.filename().string() + " to " + SavedFileAsPath.filename().string());
}

//------------------------------------------------------------------