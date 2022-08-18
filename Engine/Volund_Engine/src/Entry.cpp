#pragma once

#include "PCH/PCH.h"
#include "Core/Engine.h"
#include "Math/Math.h"
#include "Console/Console.h"

int32_t main(void)
{
	//Volund::Engine Engine;

	//Engine.LoadScenes("Scenes");

	Volund::Vec<4, float> Test = Volund::Vec4(30.0f, 20.0f, 20.0f, 20.0f) / Volund::Vec4(2.0f, 4.0f, 2.0f, 4.0f);
	//Volund::Vec3 Test2 = Volund::Vec3(2.0f, 4.0f, 5.0f);

	//Test.X = 15;
	//Test.R += 15;

	//Test /= Test2;

	Volund::Console::Log(Test);

	return 0;
}