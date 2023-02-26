#include "PCH/PCH.h"

#include "Lua/LuaComponent/LuaComponent.h"
#include "Lua/LuaMesh/LuaMesh.h"
#include "Lua/LuaMaterial/LuaMaterial.h"
#include "Lua/LuaVec/LuaVec.h"
#include "Lua/LuaSound/LuaSound.h"
#include "Lua/LuaFramebuffer/LuaFramebuffer.h"

#define VOLUND_BASE_TABLE(EntityInstance) "Entity", EntityInstance

namespace Volund
{
	template<>
	sol::table GenerateComponentTable<Camera>(sol::this_state S, const LuaEntity& E, Ref<Camera> C)
	{
		sol::state_view StateView = S;

		sol::table Table = StateView.create_table_with(VOLUND_BASE_TABLE(E),
			//FOV
			"GetFOV", std::function([C](sol::table Self) { return C->FOV; }),
			"SetFOV", std::function([C](sol::table Self, float FOV) { C->FOV = FOV; }),
			//NearPlane
			"GetNearPlane", std::function([C](sol::table Self) { return C->NearPlane; }),
			"SetNearPlane", std::function([C](sol::table Self, float NearPlane) { C->NearPlane = NearPlane; }),
			//FarPlane
			"GetFarPlane", std::function([C](sol::table Self) { return C->FarPlane; }),
			"SetFarPlane", std::function([C](sol::table Self, float FarPlane) { C->FarPlane = FarPlane; }),
			//TargetBuffer
			"SetTargetBuffer", std::function([C](sol::table Self, LuaFramebuffer TargetBuffer) { C->SetTargetBuffer(TargetBuffer.Get()); }),
			//LayerMask
			"SetLayerMask", std::function([C](sol::table Self, uint8_t Index, bool Enabled) { C->SetLayerMask(Index, Enabled); })
		);

		return Table;
	}

	template<>
	sol::table GenerateComponentTable<CameraMovement>(sol::this_state S, const LuaEntity& E, Ref<CameraMovement> C)
	{
		sol::state_view StateView = S;

		sol::table Table = StateView.create_table_with(VOLUND_BASE_TABLE(E),
			//Speed
			"GetSpeed", std::function([C](sol::table Self) { return C->Speed; }),
			"SetSpeed", std::function([C](sol::table Self, float Speed) { C->Speed = Speed; }),
			//Sensitivity
			"GetSensitivity", std::function([C](sol::table Self) { return C->Sensitivity; }),
			"SetSensitivity", std::function([C](sol::table Self, float Sensitivity) { C->Sensitivity = Sensitivity; })
		);

		return Table;
	}

	template<>
	sol::table GenerateComponentTable<MeshRenderer>(sol::this_state S, const LuaEntity& E, Ref<MeshRenderer> C)
	{
		sol::state_view StateView = S;

		sol::table Table = StateView.create_table_with(VOLUND_BASE_TABLE(E),
			//Mesh
			"GetMesh", std::function([C](sol::table Self) { return LuaMesh(C->GetMesh()); }),
			"SetMesh", std::function([C](sol::table Self, LuaMesh Mesh) { C->SetMesh(Mesh.Get()); }),
			//Material
			"GetMaterial", std::function([C](sol::table Self) { return LuaMaterial(C->GetMaterial()); }),
			"Material", std::function([C](sol::table Self, LuaMaterial Material) { C->SetMaterial(Material.Get()); }),
			//LayerMask
			"SetLayer", std::function([C](sol::table Self, uint8_t Layer) { C->SetLayer(Layer); })
		);

		return Table;
	}

	template<>
	sol::table GenerateComponentTable<PointLight>(sol::this_state S, const LuaEntity& E, Ref<PointLight> C)
	{
		sol::state_view StateView = S;

		sol::table Table = StateView.create_table_with(VOLUND_BASE_TABLE(E),
			//Color
			"GetColor", std::function([C](sol::table Self) { return C->Color; }),
			"SetColor", std::function([C](sol::table Self, const LuaVec3& Color) { C->Color = Color; }),
			//Brightness
			"GetBrightness", std::function([C](sol::table Self) { return C->Brightness; }),
			"SetBrightness", std::function([C](sol::table Self, float Brightness) { C->Brightness = Brightness; })
		);

		return Table;
	}

	template<>
	sol::table GenerateComponentTable<Script>(sol::this_state S, const LuaEntity& E, Ref<Script> C)
	{
		return C->Table;
	}

	template<>
	sol::table GenerateComponentTable<Tag>(sol::this_state S, const LuaEntity& E, Ref<Tag> C)
	{
		sol::state_view StateView = S;

		sol::table Table = StateView.create_table_with(VOLUND_BASE_TABLE(E),
			//String
			"Get", std::function([C](sol::table Self) { return C->String; }),
			"Set", std::function([C](sol::table Self, std::string String) { C->String = String; })
		);

		return Table;
	}

	template<>
	sol::table GenerateComponentTable<Transform>(sol::this_state S, const LuaEntity& E, Ref<Transform> C)
	{
		sol::state_view StateView = S;

		sol::table Table = StateView.create_table_with(VOLUND_BASE_TABLE(E),
			//Position
			"GetPosition", std::function([C](sol::table Self) { return LuaVec3(C->Position); }),
			"SetPosition", std::function([C](sol::table Self, const LuaVec3& Position) { C->Position = Position.GLM(); }),
			"AddPosition", std::function([C](sol::table Self, const LuaVec3& Position) { C->Position += Position.GLM(); }),
			//Rotation
			"GetRotation", std::function([C](sol::table Self) { return LuaVec3(C->GetRotation()); }),
			"SetRotation", std::function([C](sol::table Self, const LuaVec3& Rotation) { C->SetRotation(Rotation.GLM()); }),
			"AddRotation", std::function([C](sol::table Self, const LuaVec3& Rotation) { C->AddRotation(Rotation.GLM()); }),
			//Scale
			"GetScale", std::function([C](sol::table Self) { return LuaVec3(C->Scale); }),
			"SetScale", std::function([C](sol::table Self, const LuaVec3& Scale) { C->Scale = Scale.GLM(); }),
			"AddScale", std::function([C](sol::table Self, const LuaVec3& Scale) { C->Scale += Scale.GLM(); }),
			//Directions
			"GetFront", std::function([C](sol::table Self) { return LuaVec3(C->GetFront()); }),
			"GetRight", std::function([C](sol::table Self) { return LuaVec3(C->GetRight()); }),
			"GetUp", std::function([C](sol::table Self) { return LuaVec3(C->GetUp()); })
		);

		return Table;
	}

	template<>
	sol::table GenerateComponentTable<SoundSource>(sol::this_state S, const LuaEntity& E, Ref<SoundSource> C)
	{
		sol::state_view StateView = S;

		sol::table Table = StateView.create_table_with(VOLUND_BASE_TABLE(E),
			"Play", std::function([C](sol::table Self) { C->Play(); }),
			"SetSound", std::function([C](sol::table Self, LuaSound Sound) { C->SetBuffer(Sound.GetBuffer()); }),
			"SetPitch", std::function([C](sol::table Self, float Pitch) { C->SetPitch(Pitch); }),
			"SetLooping", std::function([C](sol::table Self, bool Looping) { C->SetLooping(Looping); }),
			"SetGain", std::function([C](sol::table Self, float Gain) { C->SetGain(Gain); })
		);

		return Table;
	}

	template<>
	sol::table GenerateComponentTable<SoundListener>(sol::this_state S, const LuaEntity& E, Ref<SoundListener> C)
	{
		sol::state_view StateView = S;

		sol::table Table = StateView.create_table_with(VOLUND_BASE_TABLE(E));

		return Table;
	}
}