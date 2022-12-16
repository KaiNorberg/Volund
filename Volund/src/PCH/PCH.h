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
#include <queue>
#include <cstdarg>
#include <filesystem>
#include <fstream>
#include <future>
#include <memory>
#include <string_view>

#define SOL_NO_EXCEPTIONS 0
#define SOL_PRINT_ERRORS 0

#include <sol/sol.hpp>

#include <glm/glm/glm.hpp>
#include <glm/glm/vec2.hpp>
#include <glm/glm/gtx/norm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include "Core/Core.h"
#include "Utils/Utils.h"
#include "Logger/Logger.h"
