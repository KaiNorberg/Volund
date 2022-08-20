#pragma once

#define CONFIG_JSON "Config.json"

#ifdef VOLUND_BUILD_DLL
	#define VOLUND_API __declspec(dllexport)
#else
	#define VOLUND_API __declspec(dllimport)
#endif