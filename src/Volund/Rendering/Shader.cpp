
#include "Rendering/Shader.hpp"
#include "Rendering/OpenGL/OpenGLShader.hpp"
#include "Rendering/RenderingAPI.hpp"
#include "Lua/LuaAPI.hpp"

namespace Volund
{
	std::shared_ptr<Shader> Shader::Create(std::string const& filepath)
	{		
		switch (RenderingAPI::GetSelectedAPI())
		{
		case GraphicsAPI::OpenGL:
		{
			return std::make_shared<OpenGLShader>(filepath);
		}
		break;
		default:
		{
			VOLUND_ERROR("Creating a Shader without a specified GraphicsAPI!");
			return nullptr;
		}
		break;
		}
	}

    VOLUND_USERTYPE_REGISTER(Shader, 
    [](LuaState* state){
        state->NewUsertype<Shader>("Shader", sol::constructors<>(),
            "new", [state](std::string const& filepath) { return Shader::Create(state->AbsolutePath(filepath)); },
            "has_uniform", &Shader::HasUniform,
            "get_id", &Shader::GetId,
            "set_int", &Shader::SetInt,
            "set_float", &Shader::SetFloat,
            "set_double", &Shader::SetDouble,
            "set_vec2", &Shader::SetVec2,
            "set_vec3", &Shader::SetVec3,
            "set_vec4", &Shader::SetVec4,
            "set_mat4x4", &Shader::SetMat4x4,
            "set_texture", &Shader::SetTexture,
            "set_framebuffer", &Shader::SetFramebuffer
        );
    });
} //namespace Volund