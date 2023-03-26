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
	sol::table GenerateComponentTable<Camera>(sol::this_state s, const LuaEntity& e, Ref<Camera> c)
	{
		sol::state_view stateView = s;

		sol::table table = stateView.create_table_with(VOLUND_BASE_TABLE(e),
			//FOV
			"GetFOV", std::function([c](sol::table self) { return c->FOV; }),
			"SetFOV", std::function([c](sol::table self, float fov) { c->FOV = fov; }),
			//NearPlane
			"GetNearPlane", std::function([c](sol::table self) { return c->NearPlane; }),
			"SetNearPlane", std::function([c](sol::table self, float nearPlane) { c->NearPlane = nearPlane; }),
			//FarPlane
			"GetFarPlane", std::function([c](sol::table self) { return c->FarPlane; }),
			"SetFarPlane", std::function([c](sol::table self, float farPlane) { c->FarPlane = farPlane; }),
			//TargetBuffer
			"SetTargetBuffer", std::function([c](sol::table self, LuaFramebuffer targetBuffer) { c->SetTargetBuffer(targetBuffer.Get()); }),
			//LayerMask
			"SetLayerMask", std::function([c](sol::table self, uint8_t index, bool enabled) { c->SetLayerMask(index, enabled); })
		);

		return table;
	}

	template<>
	sol::table GenerateComponentTable<CameraMovement>(sol::this_state s, const LuaEntity& e, Ref<CameraMovement> c)
	{
		sol::state_view stateView = s;

		sol::table table = stateView.create_table_with(VOLUND_BASE_TABLE(e),
			//Speed
			"GetSpeed", std::function([c](sol::table self) { return c->Speed; }),
			"SetSpeed", std::function([c](sol::table self, float speed) { c->Speed = speed; }),
			//Sensitivity
			"GetSensitivity", std::function([c](sol::table self) { return c->Sensitivity; }),
			"SetSensitivity", std::function([c](sol::table self, float sensitivity) { c->Sensitivity = sensitivity; })
		);

		return table;
	}

	template<>
	sol::table GenerateComponentTable<MeshRenderer>(sol::this_state s, const LuaEntity& e, Ref<MeshRenderer> c)
	{
		sol::state_view stateView = s;

		sol::table table = stateView.create_table_with(VOLUND_BASE_TABLE(e),
			//Mesh
			"GetMesh", std::function([c](sol::table self) { return LuaMesh(c->GetMesh()); }),
			"SetMesh", std::function([c](sol::table self, LuaMesh mesh) { c->SetMesh(mesh.Get()); }),
			//Material
			"GetMaterial", std::function([c](sol::table self) { return LuaMaterial(c->GetMaterial()); }),
			"Material", std::function([c](sol::table self, LuaMaterial material) { c->SetMaterial(material.Get()); }),
			//LayerMask
			"SetLayer", std::function([c](sol::table self, uint8_t layer) { c->SetLayer(layer); })
		);

		return table;
	}

	template<>
	sol::table GenerateComponentTable<PointLight>(sol::this_state s, const LuaEntity& e, Ref<PointLight> c)
	{
		sol::state_view stateView = s;

		sol::table table = stateView.create_table_with(VOLUND_BASE_TABLE(e),
			//Color
			"GetColor", std::function([c](sol::table self) { return c->Color; }),
			"SetColor", std::function([c](sol::table self, const LuaVec3& color) { c->Color = color; }),
			//Brightness
			"GetBrightness", std::function([c](sol::table self) { return c->Brightness; }),
			"SetBrightness", std::function([c](sol::table self, float brightness) { c->Brightness = brightness; })
		);

		return table;
	}

	template<>
	sol::table GenerateComponentTable<Script>(sol::this_state s, const LuaEntity& e, Ref<Script> c)
	{
		return c->Table;
	}

	template<>
	sol::table GenerateComponentTable<Tag>(sol::this_state s, const LuaEntity& e, Ref<Tag> c)
	{
		sol::state_view stateView = s;

		sol::table table = stateView.create_table_with(VOLUND_BASE_TABLE(e),
			//String
			"Get", std::function([c](sol::table self) { return c->String; }),
			"Set", std::function([c](sol::table self, const std::string string) { c->String = string; })
		);

		return table;
	}

	template<>
	sol::table GenerateComponentTable<Transform>(sol::this_state s, const LuaEntity& e, Ref<Transform> c)
	{
		sol::state_view stateView = s;

		sol::table table = stateView.create_table_with(VOLUND_BASE_TABLE(e),
			//Position
			"GetPosition", std::function([c](sol::table self) { return LuaVec3(c->Position); }),
			"SetPosition", std::function([c](sol::table self, const LuaVec3& position) { c->Position = position.GLM(); }),
			"AddPosition", std::function([c](sol::table self, const LuaVec3& position) { c->Position += position.GLM(); }),
			//Rotation
			"GetRotation", std::function([c](sol::table self) { return LuaVec3(c->GetRotation()); }),
			"SetRotation", std::function([c](sol::table self, const LuaVec3& rotation) { c->SetRotation(rotation.GLM()); }),
			"AddRotation", std::function([c](sol::table self, const LuaVec3& rotation) { c->AddRotation(rotation.GLM()); }),
			//Scale
			"GetScale", std::function([c](sol::table self) { return LuaVec3(c->Scale); }),
			"SetScale", std::function([c](sol::table self, const LuaVec3& scale) { c->Scale = scale.GLM(); }),
			"AddScale", std::function([c](sol::table self, const LuaVec3& scale) { c->Scale += scale.GLM(); }),
			//Directions
			"GetFront", std::function([c](sol::table self) { return LuaVec3(c->GetFront()); }),
			"GetRight", std::function([c](sol::table self) { return LuaVec3(c->GetRight()); }),
			"GetUp", std::function([c](sol::table self) { return LuaVec3(c->GetUp()); })
		);

		return table;
	}

	template<>
	sol::table GenerateComponentTable<SoundSource>(sol::this_state s, const LuaEntity& e, Ref<SoundSource> c)
	{
		sol::state_view stateView = s;

		sol::table table = stateView.create_table_with(VOLUND_BASE_TABLE(e),
			"Play", std::function([c](sol::table self) { c->Play(); }),
			"SetSound", std::function([c](sol::table self, LuaSound sound) { c->SetBuffer(sound.GetBuffer()); }),
			"SetPitch", std::function([c](sol::table self, float pitch) { c->SetPitch(pitch); }),
			"SetLooping", std::function([c](sol::table self, bool looping) { c->SetLooping(looping); }),
			"SetGain", std::function([c](sol::table self, float gain) { c->SetGain(gain); })
		);

		return table;
	}

	template<>
	sol::table GenerateComponentTable<SoundListener>(sol::this_state s, const LuaEntity& e, Ref<SoundListener> c)
	{
		sol::state_view stateView = s;

		sol::table table = stateView.create_table_with(VOLUND_BASE_TABLE(e));

		return table;
	}
}