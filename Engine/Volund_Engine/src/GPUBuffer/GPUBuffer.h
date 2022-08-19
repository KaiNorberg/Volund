#pragma once

#include <GL/glew.h>

namespace Volund
{
	/// <summary>
	/// Stores data on the graphics card.
	/// </summary>
	class GPUBuffer 
	{
	public:
		
		/// <summary>
		/// Inits the buffer, (should only be called once) (will be called in the non default constructor).
		/// </summary>
		/// <param name="TextureType">Default: GL_TEXTURE_2D</param>
		/// <param name="InternalFormat">Default: GL_RGBA16</param>
		/// <param name="DataFormat">Default: GL_RGBA</param>
		/// <param name="DataType">Default: GL_UNSIGNED_INT</param>
		/// <param name="WrapType">Default: GL_MIRRORED_REPEAT</param>
		/// <param name="SamplingType">Default: GL_NEAREST</param>
		/// <param name="Attachment">Default: GL_COLOR_ATTACHMENT0</param>
		/// <param name="GiveRenderBuffer">Default: false</param>
		/// <param name="Data">Default: nullptr</param>
		virtual void Init(IVec2 Size,
			GLenum TextureType = GL_TEXTURE_2D, GLenum InternalFormat = GL_RGBA16, GLenum DataFormat = GL_RGBA, 
			GLenum DataType = GL_UNSIGNED_INT, GLenum WrapType = GL_MIRRORED_REPEAT, GLenum SamplingType = GL_NEAREST, 
			GLenum Attachment = GL_COLOR_ATTACHMENT0, bool GiveRenderBuffer = false, unsigned char* Data = nullptr);

		/// <summary>
		/// Fills the buffer with the specified color.
		/// </summary>
		virtual void Clear(RGBA ClearColor = RGBA(0.0f, 0.0f, 0.0f, 1.0f));

		/// <summary>
		/// Sets the opengl viewport to be the same size as the buffers size.
		/// </summary>
		virtual void ViewPort();

		/// <summary>
		/// Binds the framebuffer of the buffer.
		/// </summary>
		virtual void BindFramebuffer();

		/// <summary>
		/// Changes the size of the buffers texture, this also clears the buffer.
		/// </summary>
		virtual void Resize(IVec2 const& NewSize);

		/// <summary>
		/// Binds the texture of the buffer and returns the assigned unit. (Can get the assigned unit by calling GetTexUnit())
		/// </summary>
		virtual uint32_t BindTex();

		/// <summary>
		/// The frameBuffer of the buffer.
		/// </summary>
		uint32_t const& FrameBufferID = FrameBufferID_P;

		/// <summary>
		/// The renderBuffer of the buffer.
		/// </summary>
		uint32_t const& RenderBufferID = RenderBufferID_P;

		/// <summary>
		/// The texture id of the buffer.
		/// </summary>
		uint32_t const& TextureBufferID = TextureBufferID_P;

		/// <summary>
		/// The size of the buffers texture.
		/// </summary>
		IVec2 const& Size = Size_P;

		/// <summary>
		/// The maximum texture unit that the buffer can be assigned to.
		/// </summary>
		GLint const& MaxTextureUnit = MaxTextureUnit_P;

		GPUBuffer() = default;

		GPUBuffer(IVec2 Size,
			GLenum TextureType = GL_TEXTURE_2D, GLenum InternalFormat = GL_RGBA16, GLenum DataFormat = GL_RGBA,
			GLenum DataType = GL_UNSIGNED_INT, GLenum WrapType = GL_MIRRORED_REPEAT, GLenum SamplingType = GL_NEAREST,
			GLenum Attachment = GL_COLOR_ATTACHMENT0, bool GiveRenderBuffer = false, unsigned char* Data = nullptr);

		virtual ~GPUBuffer();

	protected:

		GLint MaxTextureUnit_P = 0;

		GLenum TextureType = 0;

		GLenum DataType = 0;		
		
		GLenum DataFormat = 0;

		GLenum InternalFormat = 0;

		IVec2 Size_P = IVec2(0);

		uint32_t FrameBufferID_P = NULL;

		uint32_t RenderBufferID_P = NULL;

		uint32_t TextureBufferID_P = NULL;
	};

} //namespace Volund