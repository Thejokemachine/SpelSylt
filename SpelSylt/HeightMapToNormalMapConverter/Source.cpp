#ifdef _DEBUG
#pragma comment(lib, "sfml-system-d")
#pragma comment(lib, "sfml-window-d")
#pragma comment(lib, "sfml-graphics-d")
#else
#pragma comment(lib, "sfml-system")
#pragma comment(lib, "sfml-window")
#pragma comment(lib, "sfml-graphics")
#endif

#include <string>
#include <fstream>

#include "HeightMapToNormalMapConverter/MessagePrinter.h"
#include "HeightMapToNormalMapConverter/NormalMapBuilder.h"

bool ReadPaths(std::string& OutInputPath, std::string& OutOutputPath)
{
	std::ifstream ConfigStream("Paths.cfg");
	
	if (!ConfigStream.is_open())
	{
		MessagePrinter::PrintError(
			"Can not find Paths.cfg. Cannot generate any texture assets! "
			"Ensure this file exists within the application directory before running the generator!" );
		return false;
	}

	ConfigStream >> OutInputPath;
	ConfigStream >> OutOutputPath;
	ConfigStream.close();

	return true;
}

int main()
{
	std::string InPath;
	std::string OutPath;

	if (!ReadPaths(InPath, OutPath))
	{
		std::cin.get();
		return -1;
	}

	CNormalMapBuilder NMBuilder;
	NMBuilder.GenerateNMForEachHMInDirectory(InPath);

	std::cin.get();
	return 0;
}