#pragma once

#include "SpelSylt/sfml_libs.h"

#ifdef _DEBUG
#pragma comment(lib, "SSEngine/SpelSylt_Debug")
#pragma comment(lib, "RapidJson/RapidJson_Debug")
#else
#pragma comment(lib, "SSEngine/SpelSylt_Release")
#pragma comment(lib, "RapidJson/RapidJson_Release")
#endif
