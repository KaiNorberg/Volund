#include "PCH/PCH.h"
#include "Context.h"
#include "OpenGLContext.h"

#include <glad/include/glad/glad.h>

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
			VOLUND_ERROR(output.c_str());
			break;

		case GL_DEBUG_SEVERITY_MEDIUM:
			VOLUND_WARNING(output.c_str());
			break;

		case GL_DEBUG_SEVERITY_LOW:
			VOLUND_WARNING(output.c_str());
			break;

		case GL_DEBUG_SEVERITY_NOTIFICATION:
			VOLUND_INFO(output.c_str());
			break;

		default:
			VOLUND_ERROR(output.c_str());
			break;
		}
	}

	void OpenGLContext::Flush()
	{
		glViewport(0, 0, (GLsizei)this->_Window->GetSize().x, (GLsizei)this->_Window->GetSize().y);
		_Window->SwapBuffers();
	}

	OpenGLContext::OpenGLContext(Ref<Window>& window)
	{
		this->_Window = window;		
		VOLUND_INFO("Creating OpenGL context...");

		VOLUND_ASSERT(gladLoadGLLoader((GLADloadproc)_Window->GetProcAddress), "Failed to initialize OpenGL context");

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(ErrorCallback, NULL);

		VOLUND_INFO("OpenGL Renderer: %s", (const char*)glGetString(GL_RENDERER));
		VOLUND_INFO("OpenGL Version: %s", (const char*)glGetString(GL_VERSION));
		VOLUND_INFO("OpenGL Vendor: %s", (const char*)glGetString(GL_VENDOR));
	}

	OpenGLContext::~OpenGLContext()
	{

	}
}