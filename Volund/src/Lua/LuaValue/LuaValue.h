#pragma once

struct lua_State;

#define NULL_LUA 4294967295

namespace Volund
{
	class LuaValue
	{
	public:

		bool IsInt();

		bool IsString();

		bool IsNumber();

		bool IsTable();

		int64_t Int();

		std::string String();

		float Number();

		int64_t Int(const std::string& Key);

		std::string String(const std::string& Key);

		float Number(const std::string& Key);

		Vec3 Vector3(const std::string& Key);

		int64_t Int(const uint64_t Index);

		std::string String(const uint64_t Index);

		float Number(const uint64_t Index);

		operator int64_t();

		operator std::string();

		operator float();

		LuaValue(const uint64_t Index, lua_State* State);

		LuaValue(const std::string& Name, lua_State* State);

	private:

		uint64_t GetIndex();

		uint64_t _Index = 0;

		std::string _Name;
		
		lua_State* _State = nullptr;
	};
}