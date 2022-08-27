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

#include <glad/include/glad/glad.h>

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

using Vec2 = glm::vec2;
using Vec3 = glm::vec3; 
using Vec4 = glm::vec4;
using RGBA = glm::vec4;
using Quat = glm::quat;
using Mat3x3 = glm::mat3x3; 
using Mat4x4 = glm::mat4x4;

///////////////////////////////

#include "Core/Core.h"
#include "Logger/Logger.h"
