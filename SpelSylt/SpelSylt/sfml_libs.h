#pragma once


#ifdef _DEBUG
#pragma comment(lib, "SFML/sfml-audio-d.lib")
#pragma comment(lib, "SFML/sfml-graphics-d.lib")
#pragma comment(lib, "SFML/sfml-main-d.lib")
#pragma comment(lib, "SFML/sfml-network-d.lib")
#pragma comment(lib, "SFML/sfml-system-d.lib")
#pragma comment(lib, "SFML/sfml-window-d.lib")
#else
#pragma comment(lib, "SFML/sfml-audio.lib")
#pragma comment(lib, "SFML/sfml-graphics.lib")
#pragma comment(lib, "SFML/sfml-main.lib")
#pragma comment(lib, "SFML/sfml-network.lib")
#pragma comment(lib, "SFML/sfml-system.lib")
#pragma comment(lib, "SFML/sfml-window.lib")
#endif