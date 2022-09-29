#include "PCH/PCH.h"
#include "OpenGLUniformBuffer.h"

#include <glad/include/glad/glad.h>

namespace Volund
{
	void OpenGLUniformBuffer::Set(const std::string& Name, const void* Data)
	{
		if (this->_ID != 0)
		{
			Uniform uniform = this->_Uniforms[Name];
			glBindBuffer(GL_UNIFORM_BUFFER, this->_ID);
			glBufferSubData(GL_UNIFORM_BUFFER, uniform.Offset, uniform.DataSize, Data);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}
		else
		{
			VOLUND_INFO("Uniform Buffer Not Allocated!");
		}
	}

	void OpenGLUniformBuffer::Allocate(uint32_t Binding)
	{
		glGenBuffers(1, &this->_ID);
		glBindBuffer(GL_UNIFORM_BUFFER, this->_ID);
		glBufferData(GL_UNIFORM_BUFFER, this->_Size, nullptr, GL_DYNAMIC_DRAW); // allocate 152 bytes of memory
		glBindBufferBase(GL_UNIFORM_BUFFER, Binding, this->_ID);
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		if (this->_ID != 0)
		{
			glDeleteBuffers(1, &this->_ID);
		}
	}
}