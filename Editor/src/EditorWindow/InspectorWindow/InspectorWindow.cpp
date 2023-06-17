#include "PCH/PCH.h"

#include "InspectorWindow.h"

#include "Editor/Editor.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

void InspectorWindow::OnProcedure(const VL::Event& e)
{
	switch (e.Type)
	{
	case VOLUND_EVENT_TYPE_RENDER:
	{
		if (ImGui::BeginTabBar(this->GetId().c_str(), ImGuiTabBarFlags_Reorderable))
		{
			if (ImGui::BeginTabItem("EntityInspector"))
			{
				this->EntityInspector();

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("MaterialInspector"))
			{
				this->MaterialInspector();

				ImGui::EndTabItem();
			}
		}
		ImGui::EndTabBar();

		ImGui::Separator();
	}
	break;
	case EDITOR_EVENT_TYPE_NEW_SCENE:
	{
		this->m_SelectedMaterial = nullptr;
	}
	break;
	}
}

void InspectorWindow::EntityInspector()
{
	auto scene = this->m_Context->GetScene();
	auto selectedEntity = this->m_Context->SelectedEntity;

	if (scene == nullptr || !scene->IsEntityRegistered(selectedEntity))
	{
		ImGui::Text("No valid entity selected!");
		return;
	}

	auto assetManager = this->m_Context->GetAssetmanager();

	//IMPORTANT: Remember to update the code below whenever a new component is implemented.

	this->ImGuiComponent<VL::Tag>("Tag", selectedEntity, [this, selectedEntity, scene](int i)
	{
		auto tag = scene->GetComponent<VL::Tag>(selectedEntity, i);

		ImGuiString("Tag", tag->String);
	});

	this->ImGuiComponent<VL::Transform>("Transform", selectedEntity, [this, selectedEntity, scene](int i)
	{
		auto transform = scene->GetComponent<VL::Transform>(selectedEntity, i);

		VL::Vec3 position = transform->Position;
		VL::Vec3 rotation = transform->GetRotation();
		VL::Vec3 scale = transform->Scale;

		ImGuiVec3("Position", position, 0.1f, 0.0f);
		ImGuiVec3("Rotation", rotation, 0.1f, 0.0f);
		ImGuiVec3("Scale", scale, 0.1f, 1.0f);

		transform->Position = position;
		transform->SetRotation(rotation);
		transform->Scale = scale;
	});

	this->ImGuiComponent<VL::MeshRenderer>("MeshRenderer", selectedEntity, [this, selectedEntity, scene, assetManager](int i)
	{
		auto meshRenderer = scene->GetComponent<VL::MeshRenderer>(selectedEntity, i);
		auto window = this->m_Context->GetWindow();

		std::string materialPath = assetManager->FetchFilepath<VL::Material>(meshRenderer->GetMaterial());
		if (ImGuiFile("Material", materialPath))
		{
			meshRenderer->SetMaterial(assetManager->Fetch<VL::Material>(materialPath));
		}

		std::string meshPath = assetManager->FetchFilepath<VL::Mesh>(meshRenderer->GetMesh());
		if (ImGuiFile("Mesh", meshPath))
		{
			meshRenderer->SetMesh(assetManager->Fetch<VL::Mesh>(meshPath));
		}
	});

	this->ImGuiComponent<VL::Camera>("Camera", selectedEntity, [this, selectedEntity, scene](int i)
	{
		auto camera = scene->GetComponent<VL::Camera>(selectedEntity, i);

		//TODO: Add targetbuffer

		ImGuiFloat("FOV", camera->FOV);
		ImGuiFloat("FarPlane", camera->FarPlane);
		ImGuiFloat("NearPlane", camera->NearPlane);
	});

	this->ImGuiComponent<VL::CameraMovement>("CameraMovement", selectedEntity, [this, selectedEntity, scene](int i)
	{
		auto cameraMovement = scene->GetComponent<VL::CameraMovement>(selectedEntity, i);

		ImGuiFloat("Speed", cameraMovement->Speed);
		ImGuiFloat("Sensitivity", cameraMovement->Sensitivity);
	});

	this->ImGuiComponent<VL::PointLight>("PointLight", selectedEntity, [this, selectedEntity, scene](int i)
	{
		auto pointLight = scene->GetComponent<VL::PointLight>(selectedEntity, i);

		std::string label = "##Color" + std::to_string((uint64_t)pointLight.get());
		ImGui::ColorPicker3(label.c_str(), glm::value_ptr(pointLight->Color), ImGuiColorEditFlags_Float);

		ImGuiFloat("Brightness", pointLight->Brightness);
	});

	this->ImGuiComponent<VL::SoundSource>("SoundSource", selectedEntity, [this, selectedEntity, scene, assetManager](int i)
	{
		auto soundSource = scene->GetComponent<VL::SoundSource>(selectedEntity, i);
		auto window = this->m_Context->GetWindow();

		//Todo: Add variables
		std::string audiobufferPath = assetManager->FetchFilepath<VL::AudioBuffer>(soundSource->GetBuffer());
		if (ImGuiFile("AudioBuffer", audiobufferPath))
		{
			soundSource->SetBuffer(assetManager->Fetch<VL::AudioBuffer>(audiobufferPath));
		}

		ImGuiBool("AutoPlay", soundSource->AutoPlay);

		bool oldLooping = soundSource->GetLooping();
		bool newLooping = oldLooping;
		ImGuiBool("Looping", newLooping);
		if (oldLooping != newLooping)
		{
			soundSource->SetLooping(newLooping);
		}

		float oldPitch = soundSource->GetPitch();
		float newPitch = oldPitch;
		ImGuiFloat("Pitch", newPitch);
		if (oldPitch != newPitch)
		{
			soundSource->SetPitch(newPitch);
		}

		float oldGain = soundSource->GetGain();
		float newGain = oldGain;
		ImGuiFloat("Gain", newGain);
		if (oldLooping != newLooping)
		{
			soundSource->SetGain(newGain);
		}
	});

	this->ImGuiComponent<VL::SoundListener>("SoundListener", selectedEntity, [this, selectedEntity, scene](int i)
	{
	});

	ImGuiAlign("Add Component", 0.5f);
	if (ImGui::Button("Add Component"))
	{
		ImGui::OpenPopup("Add Component");
	}

	if (ImGui::BeginPopup("Add Component"))
	{
		if (ImGui::MenuItem("Tag"))
		{
			scene->CreateComponent<VL::Tag>(selectedEntity);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Transform"))
		{
			scene->CreateComponent<VL::Transform>(selectedEntity);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Camera"))
		{
			scene->CreateComponent<VL::Camera>(selectedEntity);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("MeshRenderer"))
		{
			scene->CreateComponent<VL::MeshRenderer>(selectedEntity);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("PointLight"))
		{
			scene->CreateComponent<VL::PointLight>(selectedEntity);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("CameraMovement"))
		{
			scene->CreateComponent<VL::CameraMovement>(selectedEntity);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("SoundSource"))
		{
			scene->CreateComponent<VL::SoundSource>(selectedEntity);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("SoundListener"))
		{
			scene->CreateComponent<VL::SoundListener>(selectedEntity);
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}

void InspectorWindow::MaterialInspector()
{
	auto assetManager = this->m_Context->GetAssetmanager();
	if (assetManager == nullptr)
	{
		return;
	}

	std::string materialPath = assetManager->FetchFilepath<VL::Material>(this->m_SelectedMaterial);
	if (ImGuiFile("Material", materialPath))
	{
		this->m_SelectedMaterial = assetManager->Fetch<VL::Material>(materialPath);
	}
	if (this->m_SelectedMaterial == nullptr)
	{
		return;
	}

	auto materialBlueprint = this->m_SelectedMaterial->GetBlueprint();
	if (materialBlueprint == nullptr)
	{
		return;
	}

	bool changed = false;

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::Separator();
	std::string shaderPath = assetManager->FetchFilepath<VL::Shader>(this->m_SelectedMaterial->GetShader());
	if (ImGuiFile("Shader", shaderPath))
	{
		this->m_SelectedMaterial->SetShader(assetManager->Fetch<VL::Shader>(shaderPath));
	}
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
	ImGui::Separator();
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	if (ImGuiMaterialMap<int>(this->m_SelectedMaterial->IntMap(), materialBlueprint->GetUniforms(VL::MaterialUniformType::Int), ImGuiInt))
	{
		changed = true;
	}

	if (ImGuiMaterialMap<float>(this->m_SelectedMaterial->FloatMap(), materialBlueprint->GetUniforms(VL::MaterialUniformType::Float), ImGuiFloat))
	{
		changed = true;
	}

	if (ImGuiMaterialMap<double>(this->m_SelectedMaterial->DoubleMap(), materialBlueprint->GetUniforms(VL::MaterialUniformType::Double), ImGuiDouble))
	{
		changed = true;
	}

	if (ImGuiMaterialMap<VL::Vec2>(this->m_SelectedMaterial->Vec2Map(), materialBlueprint->GetUniforms(VL::MaterialUniformType::Vec2), 
		[](const std::string& key, VL::Vec2& value) { return ImGuiVec2(key, value);} ))
	{
		changed = true;
	}

	if (ImGuiMaterialMap<VL::Vec3>(this->m_SelectedMaterial->Vec3Map(), materialBlueprint->GetUniforms(VL::MaterialUniformType::Vec3), 
		[](const std::string& key, VL::Vec3& value) { return ImGuiVec3(key, value); }))
	{
		changed = true;
	}

	if (ImGuiMaterialMap<VL::Vec4>(this->m_SelectedMaterial->Vec4Map(), materialBlueprint->GetUniforms(VL::MaterialUniformType::Vec4),
		[](const std::string& key, VL::Vec4& value) { return ImGuiVec4(key, value); }))
	{
		changed = true;
	}

	if (ImGuiMaterialMap<VL::Ref<VL::Texture>>(this->m_SelectedMaterial->TextureMap(), materialBlueprint->GetUniforms(VL::MaterialUniformType::Sampler), 
		[assetManager](const std::string& key, VL::Ref<VL::Texture>& value)
		{ 
			std::string texturePath = assetManager->FetchFilepath<VL::Texture>(value);
			if (ImGuiFile(key, texturePath))
			{
				value = assetManager->Fetch<VL::Texture>(texturePath);
				return true;
			}
			else
			{
				return false;
			}
		}))
	{
		changed = true;
	}


	ImGuiAlign("Add Entry", 0.5f);
	if (ImGui::Button("Add Entry"))
	{
		ImGui::OpenPopup("Add Entry");
	}

	if (ImGui::BeginPopup("Add Entry"))
	{
		if (ImGui::MenuItem("Int"))
		{
			changed = true;
			this->m_SelectedMaterial->SetInt("NewInt", 0);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Float"))
		{
			changed = true;
			this->m_SelectedMaterial->SetFloat("NewFloat", 0.0f);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Double"))
		{
			changed = true;
			this->m_SelectedMaterial->SetDouble("NewDouble", 0.0);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Vec2"))
		{
			changed = true;
			this->m_SelectedMaterial->SetVec2("NewVec2", VL::Vec2(0.0f, 0.0f));
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Vec3"))
		{
			changed = true;
			this->m_SelectedMaterial->SetVec3("NewVec3", VL::Vec3(0.0f, 0.0f, 0.0f));
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Vec4"))
		{
			changed = true;
			this->m_SelectedMaterial->SetVec4("NewVec4", VL::Vec4(0.0f, 0.0f, 0.0f, 0.0f));
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Texture"))
		{
			changed = true;
			this->m_SelectedMaterial->SetTexture("NewTexture", nullptr);
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}

	if (changed)
	{
		assetManager->Serialize(this->m_SelectedMaterial, materialPath);
	}
}

InspectorWindow::InspectorWindow(VL::Ref<EditorContext> context)
{
	this->SetName("Inspector");

	this->m_Context = context;
}