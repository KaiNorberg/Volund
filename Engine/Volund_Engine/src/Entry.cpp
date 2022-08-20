#pragma once

#include "PCH/PCH.h"
#include "Core/Engine.h"

int32_t main(void)
{
	while (true)
	{
		Volund::Engine Engine;

		JSON ConfigFile = JSON::Load(CONFIG_JSON);
		Engine.LoadScene(ConfigFile["Engine"]["MainScene"].get<std::string>());
	}

	return 0;
}