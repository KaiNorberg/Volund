#pragma once

class Editor : public VL::Application
{
public:

	void OnRun() override;

	void OnTerminate() override;

	void OnUpdate(VL::TimeStep TS) override;

	void OnEvent(VL::Event* E) override;

private:

	void CreateProject(const std::string& Filepath, const std::string& Name);

	void Draw(VL::TimeStep TS);

	void DrawMenuBar();

	void HandleShortcuts();
	
	VL::Input _Input;
};