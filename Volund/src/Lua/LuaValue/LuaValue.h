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
		LuaValue* Table(const std::string& Key);

		template<int S>
		glm::vec<S, float> Vector(const std::string& Key);

		int64_t Int(const int32_t Index);
		std::string String(const int32_t Index);
		float Number(const int32_t Index);
		LuaValue* Table(const int32_t Index);

		operator int64_t();
		operator std::string();
		operator float();

		uint32_t Size();

		LuaValue(const int32_t Index, lua_State* State, bool ShouldPop = false);

		~LuaValue();

	private:

		int32_t _Index = 0;
		
		lua_State* _State = nullptr;

		bool _ShouldPop;
	};

	template<int S>
	inline glm::vec<S, float> LuaValue::Vector(const std::string& Key)
	{
		LuaValue* Vector = this->Table(Key);

		int VectorSize = Vector->Size();

		glm::vec<S, float> R;

		for (int i = 0; i < S; i++)
		{
			R[i] = 1.0f;
		}

		for (int i = 0; i < S && i < VectorSize; i++)
		{
			R[i] = Vector->Number(i + 1);
		}

		delete Vector;

		return R;
	}
}