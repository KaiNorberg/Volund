#include "PCH/PCH.h"
#include "ImGuiImage.h"

#include <imgui.h>

namespace Volund
{
	void ImGuiImage::SetSize(const Vec2& size)
	{
		this->m_Size = size;
	}

	Vec2 ImGuiImage::GetSize()
	{
		return this->m_Size;
	}

	void ImGuiImage::SetTexture(Ref<Texture> texture)
	{
		this->m_TextureId = texture->GetID();
	}

	void ImGuiImage::SetTexture(Ref<Framebuffer> framebuffer, uint32_t attachmentId)
	{
		this->m_TextureId = framebuffer->GetAttachment(attachmentId);
	}

	void ImGuiImage::Procedure(const Event& e)
	{
		switch (e.Type)
		{
		case EventType::Render:
		{
			if (ImGui::BeginChild(this->m_Id.c_str()))
			{
				if (FillWindow)
				{
					ImVec2 viewportSize = ImGui::GetContentRegionAvail();
					this->m_Size = Vec2(viewportSize.x, viewportSize.y);
				}

				ImGui::Image(reinterpret_cast<void*>(this->m_TextureId), ImVec2(this->m_Size.x, this->m_Size.y), ImVec2(0, 1), ImVec2(1, 0));

				ImGui::EndChild();
			}
		}
		break;
		default:
		{

		}
		break;
		}
	}

	ImGuiImage::ImGuiImage(const std::string& id, Vec2 size, Ref<Texture> texture)
	{
		this->m_Id = id;
		this->m_Size = size;
		this->SetTexture(texture);
	}

	ImGuiImage::ImGuiImage(const std::string& id, Vec2 size, Ref<Framebuffer> framebuffer, uint32_t attachmentId)
	{
		this->m_Id = id;
		this->m_Size = size;
		this->SetTexture(framebuffer, attachmentId);
	}
}