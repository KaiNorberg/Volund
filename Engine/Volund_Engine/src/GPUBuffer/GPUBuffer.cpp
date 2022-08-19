#pragma once

#include "PCH/PCH.h"
#include "GPUBuffer.h"

namespace Volund
{
	void GPUBuffer::Init(IVec2 Size, 
		GLenum TextureType, GLenum InternalFormat, GLenum DataFormat, 
		GLenum DataType, GLenum WrapType, GLenum SamplingType, 
		GLenum Attachment, bool GiveRenderBuffer, unsigned char* Data)
	{
		this->Size_P = Size;
		this->TextureType = TextureType;
		this->DataType = DataType;
		this->DataFormat = DataFormat;
		this->InternalFormat = InternalFormat;

		glGenFramebuffers(1, &FrameBufferID_P);
		this->BindFramebuffer();

		glGenTextures(1, &TextureBufferID_P);
		glBindTexture(TextureType, TextureBufferID);
		glTexImage2D(TextureType, 0, InternalFormat, this->Size.x, this->Size.y, 0, DataFormat, DataType, Data);
		glTexParameteri(TextureType, GL_TEXTURE_WRAP_S, WrapType);
		glTexParameteri(TextureType, GL_TEXTURE_WRAP_T, WrapType);
		glTexParameteri(TextureType, GL_TEXTURE_MAG_FILTER, SamplingType);
		glTexParameteri(TextureType, GL_TEXTURE_MIN_FILTER, SamplingType);
		glFramebufferTexture2D(GL_FRAMEBUFFER, Attachment, TextureType, TextureBufferID, 0);

		if (GiveRenderBuffer)
		{
			glGenRenderbuffers(1, &this->RenderBufferID_P);
			glBindRenderbuffer(GL_RENDERBUFFER, this->RenderBufferID);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, this->Size.x, this->Size.y);
			glBindRenderbuffer(GL_RENDERBUFFER, 0);

			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->RenderBufferID);
		}

		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &MaxTextureUnit_P);
	}

	void GPUBuffer::Clear(RGBA ClearColor)
	{
		this->BindFramebuffer();

		//Clear framebuffer
		glClearColor(ClearColor.r, ClearColor.g, ClearColor.b, ClearColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glViewport(0, 0, this->Size.x, this->Size.y);
	}

	void GPUBuffer::ViewPort()
	{
		glViewport(0, 0, this->Size.x, this->Size.y);
	}

	void GPUBuffer::BindFramebuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, this->FrameBufferID_P);
	}		

	void GPUBuffer::Resize(IVec2 const& NewSize)
	{
		this->Size_P = NewSize;

		glBindTexture(this->TextureType, this->TextureBufferID);
		glTexImage2D(this->TextureType, 0, this->InternalFormat, this->Size.x, this->Size.y, 0, this->DataFormat, this->DataType, nullptr);
	}

	uint32_t GPUBuffer::BindTex ()
	{
		if (MaxTextureUnit <= 0)
		{
			return 0;
		}

		static int32_t AvailableUnit = 0;
		AvailableUnit = (AvailableUnit + 1) % MaxTextureUnit;

		glActiveTexture(GL_TEXTURE0 + AvailableUnit);
		glBindTexture(this->TextureType, this->TextureBufferID);
		return AvailableUnit;
	}

	GPUBuffer::GPUBuffer(IVec2 Size,
		GLenum TextureType, GLenum InternalFormat, GLenum DataFormat,
		GLenum DataType, GLenum WrapType, GLenum SamplingType,
		GLenum Attachment, bool GiveRenderBuffer, unsigned char* Data)
	{
		this->Init(Size,
			TextureType, InternalFormat, DataFormat,
			DataType, WrapType, SamplingType,
			Attachment, GiveRenderBuffer, Data);
	}
	
	GPUBuffer::~GPUBuffer()
	{
		if (this->FrameBufferID != NULL)
		{
			glDeleteFramebuffers(1, &this->FrameBufferID);
		}
		if (this->RenderBufferID != NULL)
		{
			glDeleteRenderbuffers(1, &this->RenderBufferID);
		}
		if (this->TextureBufferID != NULL)
		{
			glDeleteTextures(1, &this->TextureBufferID);
		}
	}

} //namespace Volund