#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#define STB_IMAGE_WRITE_STATIC
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

#include <glfw/include/GLFW/glfw3.h>
#include <json/single_include/nlohmann/json.hpp>
#include "JSON/JSON.h"

///////////TEMPORARY///////////
#include <glm/glm/glm.hpp>
#include <glm/glm/vec2.hpp>
#include <glm/glm/vec3.hpp>
#include <glm/glm/vec4.hpp>
#include <glm/glm/mat4x4.hpp>
#include <glm/glm/mat3x3.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtc/quaternion.hpp>

using Vec3 = glm::vec3;
using Quat = glm::quat;
using Mat4x4 = glm::mat4x4;
///////////////////////////////

#include "Console/Console.h"
#include "Core/Core.h"