#include "PCH/PCH.h"
#include "Context.h"
#include "OpenGLContext.h"

namespace Volund
{
	void APIENTRY ErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
		GLsizei length, const GLchar* message, const void* userParam)
	{
		std::string _source;
		std::string _type;

		switch (source)
		{
		case GL_DEBUG_SOURCE_API:
			_source = "API";
			break;

		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			_source = "WINDOW SYSTEM";
			break;

		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			_source = "SHADER COMPILER";
			break;

		case GL_DEBUG_SOURCE_THIRD_PARTY:
			_source = "THIRD PARTY";
			break;

		case GL_DEBUG_SOURCE_APPLICATION:
			_source = "APPLICATION";
			break;

		default:
			_source = "UNKNOWN";
			break;
		}

		switch (type)
		{
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			_type = "DEPRECATED BEHAVIOR: ";
			break;

		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			_type = "UDEFINED BEHAVIOR: ";
			break;

		case GL_DEBUG_TYPE_PORTABILITY:
			_type = "PORTABILITY: ";
			break;

		case GL_DEBUG_TYPE_PERFORMANCE:
			_type = "PERFORMANCE: ";
			break;

		case GL_DEBUG_TYPE_MARKER:
			_type = "MARKER: ";
			break;

		case GL_DEBUG_TYPE_OTHER:
			_type = "OTHER: ";
			break;

		default:
			_type = "";
			break;
		}

		std::string output = _type + std::to_string(id) + ", raised from " + _source + ": " + message;

		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:
			VOLUND_CORE_ERROR(output.c_str());
			break;

		case GL_DEBUG_SEVERITY_MEDIUM:
			VOLUND_CORE_WARNING(output.c_str());
			break;

		case GL_DEBUG_SEVERITY_LOW:
			VOLUND_CORE_WARNING(output.c_str());
			break;

		case GL_DEBUG_SEVERITY_NOTIFICATION:
			VOLUND_CORE_INFO(output.c_str());
			break;

		default:
			VOLUND_CORE_ERROR(output.c_str());
			break;
		}
	}

	void OpenGLContext::SwapBuffers()
	{
		_Window->SwapBuffers();
	}

	OpenGLContext::OpenGLContext(Window* window)
	{
		this->_Window = window;		
		
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			VOLUND_CORE_ERROR("Failed to initialize OpenGL context");
		}

		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(ErrorCallback, NULL);
	}
}