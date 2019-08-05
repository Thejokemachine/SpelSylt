#pragma once

#include "SpelSylt/sfml_libs.h"

#ifdef _DEBUG
#pragma comment(lib, "SpelSylt_Debug")
#pragma comment(lib, "RapidJson_Debug")
#else
#pragma comment(lib, "SpelSylt_Release")
#pragma comment(lib, "RapidJson_Release")
#endif
