#pragma once

#include "../EditorWindow.h"

#include "ViewportCamera/ViewportCamera.h"

class ViewportWindow : public EditorWindow
{
public:

	void OnProcedure(const VL::Event& e) override;

	ViewportWindow(VL::Ref<EditorContext> context);

private:
	
	VL::Vec2 m_Size = VL::Vec2(100, 100);
	std::string m_Text;

	VL::Input m_Input;

	VL::Ref<VL::Texture> m_PlayIcon;
	VL::Ref<VL::Texture> m_PauseIcon;

	VL::Ref<VL::Framebuffer> m_Viewportbuffer;

	VL::Ref<ViewportCamera> m_Camera;
};

