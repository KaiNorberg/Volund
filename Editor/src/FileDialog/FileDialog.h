#pragma once

class FileDialog
{
public:
	static std::string OpenFile(const char* Filter, VL::Ref<VL::Window> Owner);

	static std::string SaveFile(const char* Filter, VL::Ref<VL::Window> Owner);
};