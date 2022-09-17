#pragma once

#pragma warning( push )
#pragma warning( disable : 4305 )

static void SetupImGuiStyle()
{
	// Darcula style by ice1000 from ImThemes
	ImGuiStyle& style = ImGui::GetStyle();

	style.Alpha = 1.0;
	style.DisabledAlpha = 0.6000000238418579;
	style.WindowPadding = ImVec2(8.0, 8.0);
	style.WindowRounding = 5.300000190734863;
	style.WindowBorderSize = 1.0;
	style.WindowMinSize = ImVec2(32.0, 32.0);
	style.WindowTitleAlign = ImVec2(0.0, 0.5);
	style.WindowMenuButtonPosition = ImGuiDir_Left;
	style.ChildRounding = 0.0;
	style.ChildBorderSize = 1.0;
	style.PopupRounding = 0.0;
	style.PopupBorderSize = 1.0;
	style.FramePadding = ImVec2(4.0, 3.0);
	style.FrameRounding = 2.299999952316284;
	style.FrameBorderSize = 1.0;
	style.ItemSpacing = ImVec2(8.0, 6.5);
	style.ItemInnerSpacing = ImVec2(4.0, 4.0);
	style.CellPadding = ImVec2(4.0, 2.0);
	style.IndentSpacing = 21.0;
	style.ColumnsMinSpacing = 6.0;
	style.ScrollbarSize = 14.0;
	style.ScrollbarRounding = 5.0;
	style.GrabMinSize = 10.0;
	style.GrabRounding = 2.299999952316284;
	style.TabRounding = 4.0;
	style.TabBorderSize = 0.0;
	style.TabMinWidthForCloseButton = 0.0;
	style.ColorButtonPosition = ImGuiDir_Right;
	style.ButtonTextAlign = ImVec2(0.5, 0.5);
	style.SelectableTextAlign = ImVec2(0.0, 0.0);

	style.Colors[ImGuiCol_Text] = ImVec4(0.7333333492279053, 0.7333333492279053, 0.7333333492279053, 1.0);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.3450980484485626, 0.3450980484485626, 0.3450980484485626, 1.0);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.2352941185235977, 0.2470588237047195, 0.2549019753932953, 0.9399999976158142);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.2352941185235977, 0.2470588237047195, 0.2549019753932953, 0.0);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.2352941185235977, 0.2470588237047195, 0.2549019753932953, 0.9399999976158142);
	style.Colors[ImGuiCol_Border] = ImVec4(0.3333333432674408, 0.3333333432674408, 0.3333333432674408, 0.5);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.1568627506494522, 0.1568627506494522, 0.1568627506494522, 0.0);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.168627455830574, 0.168627455830574, 0.168627455830574, 0.5400000214576721);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.4509803950786591, 0.6745098233222961, 0.9960784316062927, 0.6700000166893005);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.4705882370471954, 0.4705882370471954, 0.4705882370471954, 0.6700000166893005);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.03921568766236305, 0.03921568766236305, 0.03921568766236305, 1.0);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.0, 0.0, 0.0, 0.5099999904632568);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.1568627506494522, 0.2862745225429535, 0.47843137383461, 1.0);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.2705882489681244, 0.2862745225429535, 0.2901960909366608, 0.800000011920929);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.2705882489681244, 0.2862745225429535, 0.2901960909366608, 0.6000000238418579);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.2196078449487686, 0.3098039329051971, 0.4196078479290009, 0.5099999904632568);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.2196078449487686, 0.3098039329051971, 0.4196078479290009, 1.0);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.1372549086809158, 0.1921568661928177, 0.2627451121807098, 0.9100000262260437);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.8980392217636108, 0.8980392217636108, 0.8980392217636108, 0.8299999833106995);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.6980392336845398, 0.6980392336845398, 0.6980392336845398, 0.6200000047683716);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.2980392277240753, 0.2980392277240753, 0.2980392277240753, 0.8399999737739563);
	style.Colors[ImGuiCol_Button] = ImVec4(0.3333333432674408, 0.3529411852359772, 0.3607843220233917, 0.4900000095367432);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.2196078449487686, 0.3098039329051971, 0.4196078479290009, 1.0);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.1372549086809158, 0.1921568661928177, 0.2627451121807098, 1.0);
	style.Colors[ImGuiCol_Header] = ImVec4(0.3333333432674408, 0.3529411852359772, 0.3607843220233917, 0.5299999713897705);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.4509803950786591, 0.6745098233222961, 0.9960784316062927, 0.6700000166893005);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.4705882370471954, 0.4705882370471954, 0.4705882370471954, 0.6700000166893005);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.3137255012989044, 0.3137255012989044, 0.3137255012989044, 1.0);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.3137255012989044, 0.3137255012989044, 0.3137255012989044, 1.0);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.3137255012989044, 0.3137255012989044, 0.3137255012989044, 1.0);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.0, 1.0, 1.0, 0.8500000238418579);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.0, 1.0, 1.0, 0.6000000238418579);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.0, 1.0, 1.0, 0.8999999761581421);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.1764705926179886, 0.3490196168422699, 0.5764706134796143, 0.8619999885559082);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.2588235437870026, 0.5882353186607361, 0.9764705896377563, 0.800000011920929);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.196078434586525, 0.407843142747879, 0.6784313917160034, 1.0);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.06666667014360428, 0.1019607856869698, 0.1450980454683304, 0.9724000096321106);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.1333333402872086, 0.2588235437870026, 0.4235294163227081, 1.0);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.6078431606292725, 0.6078431606292725, 0.6078431606292725, 1.0);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.0, 0.4274509847164154, 0.3490196168422699, 1.0);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.8980392217636108, 0.6980392336845398, 0.0, 1.0);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0, 0.6000000238418579, 0.0, 1.0);
	style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.1882352977991104, 0.1882352977991104, 0.2000000029802322, 1.0);
	style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.3098039329051971, 0.3098039329051971, 0.3490196168422699, 1.0);
	style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.2274509817361832, 0.2274509817361832, 0.2470588237047195, 1.0);
	style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0, 0.0, 0.0, 0.0);
	style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0, 1.0, 1.0, 0.05999999865889549);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.1843137294054031, 0.3960784375667572, 0.7921568751335144, 0.8999999761581421);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0, 1.0, 0.0, 0.8999999761581421);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.2588235437870026, 0.5882353186607361, 0.9764705896377563, 1.0);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0, 1.0, 1.0, 0.699999988079071);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.800000011920929, 0.800000011920929, 0.800000011920929, 0.2000000029802322);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.800000011920929, 0.800000011920929, 0.800000011920929, 0.3499999940395355);
}

#pragma warning(pop)