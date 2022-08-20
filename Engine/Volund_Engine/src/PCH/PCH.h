#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#define STB_IMAGE_WRITE_STATIC
#define GLEW_STATIC

#define VOLUND_START_WINDOWED

#define CONFIG_JSON "Config.json"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <future>
#include <fstream>
#include <filesystem>
#include <memory>

#include <Include/glm/glm.hpp>
#include <Include/glm/vec2.hpp>
#include <Include/glm/vec3.hpp>
#include <Include/glm/vec4.hpp>
#include <Include/glm/mat4x4.hpp>
#include <Include/glm/mat3x3.hpp>
#include <Include/glm/gtc/matrix_transform.hpp>
#include <Include/glm/gtc/type_ptr.hpp>
#include <Include/glm/gtc/quaternion.hpp>

#include <Include/json/json.hpp>
#include <Include/GLFW/glfw3.h>

using Vec3 = glm::vec3;
using Quat = glm::quat;
using Mat4x4 = glm::mat4x4;

using JSON = nlohmann::json;

#include "Console/Console.h"