#include "PCH/PCH.h"

#include "OpenGLRenderingAPI.h"

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

	void OpenGLRenderingAPI::SetViewPort(int32_t X, int32_t Y, int32_t Width, int32_t Height)
	{
		glViewport(X, Y, Width, Height);
	}

	void OpenGLRenderingAPI::SetClearColor(const RGBA& Color)
	{
		glClearColor(Color.r, Color.g, Color.b, Color.a);
	}

	void OpenGLRenderingAPI::Clear()
	{
		glClear(GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRenderingAPI::DrawIndexed(const Ref<Mesh>& VArray)
	{
		glDrawElements(GL_TRIANGLES, VArray->GetIndexbuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRenderingAPI::Init()
	{
		VOLUND_ASSERT(gladLoadGL(), "Failed to load OpenGL");

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(ErrorCallback, nullptr);

		VOLUND_INFO("OpenGL Renderer: %s", (const char*)glGetString(GL_RENDERER));
		VOLUND_INFO("OpenGL Version: %s", (const char*)glGetString(GL_VERSION));
		VOLUND_INFO("OpenGL Vendor: %s", (const char*)glGetString(GL_VENDOR));
	}

	OpenGLRenderingAPI::OpenGLRenderingAPI()
	{

	}
}
