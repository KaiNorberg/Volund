
#include "Rendering/OpenGL/OpenGLRenderingAPI.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Volund
{
	void APIENTRY ErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
	                            GLsizei length, const GLchar* message, const void* userParam)
	{
		std::string sourceString;
		std::string typeString;

		switch (source)
		{
		case GL_DEBUG_SOURCE_API:
			sourceString = "API";
			break;

		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			sourceString = "WINDOW SYSTEM";
			break;

		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			sourceString = "SHADER COMPILER";
			break;

		case GL_DEBUG_SOURCE_THIRD_PARTY:
			sourceString = "THIRD PARTY";
			break;

		case GL_DEBUG_SOURCE_APPLICATION:
			sourceString = "APPLICATION";
			break;

		default:
			sourceString = "UNKNOWN";
			break;
		}

		switch (type)
		{
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			typeString = "DEPRECATED BEHAVIOR: ";
			break;

		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			typeString = "UDEFINED BEHAVIOR: ";
			break;

		case GL_DEBUG_TYPE_PORTABILITY:
			typeString = "PORTABILITY: ";
			break;

		case GL_DEBUG_TYPE_PERFORMANCE:
			typeString = "PERFORMANCE: ";
			break;

		case GL_DEBUG_TYPE_MARKER:
			typeString = "MARKER: ";
			break;

		case GL_DEBUG_TYPE_OTHER:
			typeString = "OTHER: ";
			break;

		default:
			typeString = "";
			break;
		}

		std::string output = typeString + std::to_string(id) + ", raised from " + sourceString + ": " + message;

		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:
			VOLUND_ERROR("{}", output);
			break;

		case GL_DEBUG_SEVERITY_MEDIUM:
			VOLUND_WARNING("{}", output);
			break;

		case GL_DEBUG_SEVERITY_LOW:
			VOLUND_WARNING("{}", output);
			break;

		case GL_DEBUG_SEVERITY_NOTIFICATION:
			VOLUND_INFO("{}", output);
			break;

		default:
			VOLUND_ERROR("{}", output);
			break;
		}
	}

	IVec2 OpenGLRenderingAPI::GetViewSize()
	{
		GLint viewport[4];

		glGetIntegerv(GL_VIEWPORT, viewport);

		return IVec2(viewport[2], viewport[3]);
	}

	void OpenGLRenderingAPI::SetViewPort(const int32_t x, int32_t y, int32_t width, int32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRenderingAPI::Clear(const RGBA color)
	{
		glClearColor(color.r, color.g, color.b, color.a);

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void OpenGLRenderingAPI::DrawIndexed(uint64_t indexCount)
	{
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRenderingAPI::Draw(uint64_t first, uint64_t count)
	{
		glDrawArrays(GL_TRIANGLES, first, count);
	}

	void OpenGLRenderingAPI::BlitFramebuffer(std::shared_ptr<Framebuffer> readBuffer, std::shared_ptr<Framebuffer> drawBuffer)
	{
		uint32_t readId = readBuffer->GetID();
		auto readSpec = readBuffer->GetSpec();

		uint32_t drawId;
		int32_t drawWidth;
		int32_t drawHeight;
		if (drawBuffer != nullptr)
		{
			auto drawSpec = drawBuffer->GetSpec();

			drawId = drawBuffer->GetID();
			drawWidth = drawSpec.Width;
			drawHeight = drawSpec.Height;
		}
		else
		{
			drawId = 0;

			auto currentWindow = glfwGetCurrentContext();
			glfwGetWindowSize(currentWindow, &drawWidth, &drawHeight);
		}

		glBlitNamedFramebuffer(readId, drawId, 0, 0, readSpec.Width, readSpec.Height, 0, 0, drawWidth, drawHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	}

	OpenGLRenderingAPI::OpenGLRenderingAPI()
	{
		VOLUND_ASSERT(gladLoadGL(), "Unable to load OpenGL");

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(ErrorCallback, nullptr);

		VOLUND_INFO("OpenGL Renderer: {}", glGetString(GL_RENDERER));
		VOLUND_INFO("OpenGL Version: {}", glGetString(GL_VERSION));
		VOLUND_INFO("OpenGL Vendor: {}", glGetString(GL_VENDOR));
	}
}