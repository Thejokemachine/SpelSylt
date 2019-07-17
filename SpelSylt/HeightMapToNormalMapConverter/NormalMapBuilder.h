#pragma once
#include <SFML/Graphics/Shader.hpp>
#include <string>

class CNormalMapBuilder
{
public:
	CNormalMapBuilder();

	void GenerateNMForEachHMInDirectory(const std::string& InHeightMapsDirectory);
private:
	void GenerateNM(const std::string& InPathToHM, const std::string& InDirectory);

	sf::Shader ConversionShader;
	unsigned int Count;
};