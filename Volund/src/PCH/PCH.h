#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <array>
#include <map>
#if defined(_MSC_VER)
#include <unordered_map>
#else
#include <tr/unordered_map>
#endif
#include <cstdarg>
#include <filesystem>
#include <fstream>
#include <future>
#include <memory>
#include <string_view>

#define SOL_NO_EXCEPTIONS 0
#define SOL_PRINT_ERRORS 1

#include <sol/sol.hpp>

#include "Math/Math.h"

#include "Core/Core.h"
#include "Logger/Logger.h"
