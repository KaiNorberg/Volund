#pragma once

#include "../ImGuiObject.h"

#include "Renderer/Texture/Texture.h"
#include "Renderer/Framebuffer/Framebuffer.h"

namespace Volund
{	
	class ImGuiImage : public ImGuiObject
	{
	public:

		bool FillWindow = false;

		void SetSize(const Vec2& size);

		Vec2 GetSize();

		void SetTexture(Ref<Texture> texture);

		void SetTexture(Ref<Framebuffer> framebuffer, uint32_t attachmentId = 0);

		void Procedure(const Event& e) override;

		ImGuiImage(const std::string& id, Vec2 size, Ref<Texture> texture);

		ImGuiImage(const std::string& id, Vec2 size, Ref<Framebuffer> framebuffer, uint32_t attachmentId = 0);

	private:

		Vec2 m_Size;

		uint32_t m_TextureId;

		std::string m_Text;
	};
}

