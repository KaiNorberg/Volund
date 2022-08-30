#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define GLEW_STATIC

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#if defined(_MSC_VER)
# include <unordered_map>
#else
# include <tr/unordered_map>
#endif
#include <future>
#include <fstream>
#include <filesystem>
#include <memory>
#include <cstdarg>

#include "JSON/JSON.h"

#include "Math/Math.h"

#include "Core/Core.h"
#include "Logger/Logger.h"
