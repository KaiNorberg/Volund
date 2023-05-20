#include "PCH/PCH.h"

#include "SceneSerializer.h"

#include "Scene/Component/Components.h"

namespace Volund
{
	SceneSerializer::SceneSerializer(Ref<Scene> scene)
	{
		VOLUND_INFO("Serializing Scene");

		this->StartTable();
		for (auto& [entity, polyContainer] : (*scene))
		{
			this->SerializeEntity(scene, entity);
		}
		this->EndTable();
	}

	void SceneSerializer::SerializeEntity(Ref<Scene> scene, Entity entity)
	{           
		//IMPORTANT: Remember to update the code below whenever a new component is implemented.

		this->StartTable();

		for (int i = 0; i < scene->ComponentAmount<Tag>(entity); i++)
		{
			auto component = scene->GetComponent<Tag>(entity, i);

			this->StartTable();
			this->Insert("", "state.Enums.Component.Tag", false);
			this->Insert("String", component->String);
			this->EndTable();
		}

		for (int i = 0; i < scene->ComponentAmount<Transform>(entity); i++)
		{
			auto component = scene->GetComponent<Transform>(entity, i);

			this->StartTable();
			this->Insert("", "state.Enums.Component.Transform", false);
			this->Insert("Position", component->Position);
			this->Insert("Rotation", component->GetRotation());
			this->Insert("Scale", component->Scale);
			this->EndTable();
		}

		for (int i = 0; i < scene->ComponentAmount<Camera>(entity); i++)
		{
			auto component = scene->GetComponent<Camera>(entity, i);

			this->StartTable();
			this->Insert("", "state.Enums.Component.Camera", false);
			this->Insert("FOV", component->FOV);
			this->Insert("NearPlane", component->NearPlane);
			this->Insert("FarPlane", component->FarPlane);
			//TODO: Insert targetbuffer
			this->EndTable();
		}

		for (int i = 0; i < scene->ComponentAmount<CameraMovement>(entity); i++)
		{
			auto component = scene->GetComponent<CameraMovement>(entity, i);

			this->StartTable();
			this->Insert("", "state.Enums.Component.CameraMovement", false);
			this->Insert("Speed", component->Speed);
			this->Insert("Sensitivity", component->Sensitivity);
			this->EndTable();
		}

		for (int i = 0; i < scene->ComponentAmount<MeshRenderer>(entity); i++)
		{
			auto component = scene->GetComponent<MeshRenderer>(entity, i);

			std::string meshPath = scene->FetchAssetFilepath(component->GetMesh());
			std::replace(meshPath.begin(), meshPath.end(), '\\', '/');

			std::string materialPath = scene->FetchAssetFilepath(component->GetMaterial());
			std::replace(materialPath.begin(), materialPath.end(), '\\', '/');

			this->StartTable();
			this->Insert("", "state.Enums.Component.MeshRenderer", false);
			this->Insert("Mesh", meshPath);
			this->Insert("Material", materialPath);
			this->EndTable();
		}

		for (int i = 0; i < scene->ComponentAmount<PointLight>(entity); i++)
		{
			auto component = scene->GetComponent<PointLight>(entity, i);

			this->StartTable();
			this->Insert("", "state.Enums.Component.PointLight", false);
			this->Insert("Color", component->Color);
			this->Insert("Brightness", component->Brightness);
			this->EndTable();
		}

		for (int i = 0; i < scene->ComponentAmount<SoundSource>(entity); i++)
		{
			auto component = scene->GetComponent<SoundSource>(entity, i);

			this->StartTable();
			this->Insert("", "state.Enums.Component.SoundSource", false);
			this->Insert("Looping", component->GetLooping());
			this->Insert("Pitch", component->GetPitch());
			this->Insert("Gain", component->GetGain());
			this->Insert("AutoPlay", component->AutoPlay);
			this->EndTable();
		}

		for (int i = 0; i < scene->ComponentAmount<SoundListener>(entity); i++)
		{
			auto component = scene->GetComponent<SoundListener>(entity, i);

			this->StartTable();
			this->Insert("", "state.Enums.Component.SoundListener", false);
			this->EndTable();
		}

		this->EndTable();
	}
}