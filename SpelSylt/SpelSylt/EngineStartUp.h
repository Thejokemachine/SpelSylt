#pragma once

#include "SpelSylt/sfml_libs.h"

#ifdef _DEBUG
#pragma comment(lib, "../External/Engine/SpelSylt_Debug")
#pragma comment(lib, "../External/RapidJson_Debug")
#else
#pragma comment(lib, "../External/Engine/SpelSylt_Release")
#pragma comment(lib, "../External/RapidJson_Release")
#endif

#include "SpelSylt/Application.h"

