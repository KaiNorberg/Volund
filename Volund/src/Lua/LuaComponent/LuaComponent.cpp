#include "PCH/PCH.h"

#include "Lua/LuaComponent/LuaComponent.h"

#include "Lua/LuaMesh/LuaMesh.h"
#include "Lua/LuaMaterial/LuaMaterial.h"

#define VOLUND_BASE_TABLE() "Entity", LuaEntity(C->GetScene(), C->GetEntity())

namespace Volund
{
	template<>
	sol::table GenerateComponentTable<Camera>(sol::this_state S, Ref<Camera> C)
	{
		sol::state_view StateView = S;

		sol::table Table = StateView.create_table_with(VOLUND_BASE_TABLE(),
			//FOV
			"GetFOV", [C](sol::table Self) { return C->FOV; },
			"SetFOV", [C](sol::table Self, float FOV) { C->FOV = FOV; },
			//NearPlane
			"GetNearPlane", [C](sol::table Self) { return C->NearPlane; },
			"SetNearPlane", [C](sol::table Self, float NearPlane) { C->NearPlane = NearPlane; },
			//FarPlane
			"GetFarPlane", [C](sol::table Self) { return C->FarPlane; },
			"SetFarPlane", [C](sol::table Self, float FarPlane) { C->FarPlane = FarPlane; }
		);

		return Table;
	}

	template<>
	sol::table GenerateComponentTable<CameraMovement>(sol::this_state S, Ref<CameraMovement> C)
	{
		sol::state_view StateView = S;

		sol::table Table = StateView.create_table_with(VOLUND_BASE_TABLE(),
			//Speed
			"GetSpeed", [C](sol::table Self) { return C->Speed; },
			"SetSpeed", [C](sol::table Self, float Speed) { C->Speed = Speed; },
			//Sensitivity
			"GetSensitivity", [C](sol::table Self) { return C->Sensitivity; },
			"SetSensitivity", [C](sol::table Self, float Sensitivity) { C->Sensitivity = Sensitivity; }
		);

		return Table;
	}

	template<>
	sol::table GenerateComponentTable<MeshRenderer>(sol::this_state S, Ref<MeshRenderer> C)
	{
		sol::state_view StateView = S;

		sol::table Table = StateView.create_table_with(VOLUND_BASE_TABLE(),
			//Mesh
			"GetMesh", [C](sol::table Self) { return LuaMesh(C->GetMesh()); },
			"SetMesh", [C](sol::table Self, LuaMesh Mesh) { C->SetMesh(Mesh.Get()); },
			//Material
			"GetMaterial", [C](sol::table Self) { return LuaMaterial(C->GetMaterial()); },
			"SetMaterial", [C](sol::table Self, LuaMaterial Material) { C->SetMaterial(Material.Get()); }
		);

		return Table;
	}

	template<>
	sol::table GenerateComponentTable<PointLight>(sol::this_state S, Ref<PointLight> C)
	{
		sol::state_view StateView = S;

		sol::table Table = StateView.create_table_with(VOLUND_BASE_TABLE(),
			//Color
			"GetColor", [C](sol::table Self) { return C->Color; },
			"SetColor", [C](sol::table Self, const LuaVec3& Color) { C->Color = Color; },
			//Brightness
			"GetBrightness", [C](sol::table Self) { return C->Brightness; },
			"SetBrightness", [C](sol::table Self, float Brightness) { C->Brightness = Brightness; }
		);

		return Table;
	}

	template<>
	sol::table GenerateComponentTable<Script>(sol::this_state S, Ref<Script> C)
	{
		return C->Table;
	}

	template<>
	sol::table GenerateComponentTable<Tag>(sol::this_state S, Ref<Tag> C)
	{
		sol::state_view StateView = S;

		sol::table Table = StateView.create_table_with(VOLUND_BASE_TABLE(),
			//String
			"Get", [C](sol::table Self) { return C->String; },
			"Set", [C](sol::table Self, std::string String) { C->String = String; }
		);

		return Table;
	}

	template<>
	sol::table GenerateComponentTable<Transform>(sol::this_state S, Ref<Transform> C)
	{
		sol::state_view StateView = S;

		sol::table Table = StateView.create_table_with(VOLUND_BASE_TABLE(),
			//Position
			"GetPosition", [C](sol::table Self) { return LuaVec3(C->Position); },
			"SetPosition", [C](sol::table Self, const LuaVec3& Position) { C->Position = Position.GLM(); },
			"AddPosition", [C](sol::table Self, const LuaVec3& Position) { C->Position += Position.GLM(); },
			//Rotation
			"GetRotation", [C](sol::table Self) { return LuaVec3(C->GetRotation()); },
			"SetRotation", [C](sol::table Self, const LuaVec3& Rotation) { C->SetRotation(Rotation.GLM()); },
			"AddRotation", [C](sol::table Self, const LuaVec3& Rotation) { C->AddRotation(Rotation.GLM()); },
			//Scale
			"GetScale", [C](sol::table Self) { return LuaVec3(C->Scale); },
			"SetScale", [C](sol::table Self, const LuaVec3& Scale) { C->Scale = Scale.GLM(); },
			"AddScale", [C](sol::table Self, const LuaVec3& Scale) { C->Scale += Scale.GLM(); },
			//Directions
			"GetFront", [C](sol::table Self) { return LuaVec3(C->GetFront()); },
			"GetRight", [C](sol::table Self) { return LuaVec3(C->GetRight()); },
			"GetUp", [C](sol::table Self) { return LuaVec3(C->GetUp()); }
		);

		return Table;
	}
}