#pragma once

class EditorModule : public VL::Module
{
public:

	void OnAttach(VL::Application* app) override;

	void OnDetach() override;

	void Procedure(const VL::Event& e) override;

	VL::Entity SelectedEntity;

private:

};

