#include "PCH/PCH.h"
#include "Renderer.h"

#include "Scene/Entity/Component/Transform/Transform.h"
#include "Scene/Entity/Component/PointLight/PointLight.h"

namespace Volund
{
	void Renderer::BeginScene(Mat4x4& ViewProjMatrix, Vec3& EyePosition)
	{
		_SceneData = SceneData();
		_SceneData.ViewProjMatrix = ViewProjMatrix;
		_SceneData.EyePosition = EyePosition;

		_InScene = true;
	}

	void Renderer::EndScene()
	{
		Discriminate(_SceneData.Objects);
		Sort(_SceneData.Objects);

		Shader* PreviousShader = nullptr;
		for (const Object& Data : _SceneData.Objects)
		{
			Ref<Shader> ObjectShader = Data.ObjectMaterial->GetShader();

			if (PreviousShader != ObjectShader.get())
			{
				if (ObjectShader->HasUniform("PointLights[0].Color"))
				{
					ObjectShader->SetInt("PointLightAmount", (int32_t)_SceneData.PointLights.size());

					for (uint64_t i = 0; i < _SceneData.PointLights.size(); i++)
					{
						std::string Uniform = "PointLights[" + std::to_string(i) + "].";
						ObjectShader->SetVec3(Uniform + "Color", _SceneData.PointLights[i].Color);
						ObjectShader->SetFloat(Uniform + "Brightness", _SceneData.PointLights[i].Brightness);
						ObjectShader->SetVec3(Uniform + "Position", _SceneData.PointLights[i].Position);
					}
				}

				if (ObjectShader->HasUniform("ViewProjMatrix"))
				{
					ObjectShader->SetMat4x4("ViewProjMatrix", _SceneData.ViewProjMatrix);
				}

				if (ObjectShader->HasUniform("EyePosition"))
				{
					ObjectShader->SetVec3("EyePosition", _SceneData.EyePosition);
				}

				PreviousShader = ObjectShader.get();
			}
		}

		Material* PreviousMaterial = nullptr;
		for (const Object& Data : _SceneData.Objects)
		{
			Ref<Shader> ObjectShader = Data.ObjectMaterial->GetShader();

			if (PreviousMaterial != Data.ObjectMaterial.get())
			{
				Data.ObjectMaterial->UpdateShader();

				PreviousMaterial = Data.ObjectMaterial.get();
			}

			if (ObjectShader->HasUniform("ModelMatrix"))
			{
				ObjectShader->SetMat4x4("ModelMatrix", Data.ModelMatrix);
			}

			Data.ObjectMesh->Bind();
			_API->DrawIndexed(Data.ObjectMesh);
		}

		_InScene = false;
		_SceneData = SceneData();
	}

	void Renderer::SubmitPointLight(const RGB& Color, float Brightness, const Vec3& Position)
	{
		VOLUND_ASSERT(_InScene, "Attempting to push a Submission to the Renderer while outside of a Renderer Scene!");

		PointLight NewPointLight = PointLight();
		NewPointLight.Color = Color;
		NewPointLight.Brightness = Brightness;
		NewPointLight.Position = Position;

		_SceneData.PointLights.push_back(NewPointLight);
	}

	void Renderer::SubmitObject(Mat4x4& ModelMatrix, const Ref<Mesh>& ObjectMesh, const Ref<Material>& ObjectMaterial, bool AllowDiscrimination)
	{
		VOLUND_ASSERT(_InScene, "Attempting to push a Submission to the Renderer while outside of a Renderer Scene!");

		Object NewObject = Object();
		NewObject.AllowDiscrimination = AllowDiscrimination;
		NewObject.ModelMatrix = ModelMatrix;
		NewObject.ObjectMesh = ObjectMesh;
		NewObject.ObjectMaterial = ObjectMaterial;

		_SceneData.Objects.push_back(NewObject);
	}

	void Renderer::Init(const Ref<RenderingAPI>& API)
	{
		_API = API;
		_API->Init();
	}

	void Renderer::Discriminate(std::vector<Object>& Submissions)
	{
		//TODO
	}

	void Renderer::Sort(std::vector<Object>& Submissions)
	{
		//TODO
	}
}
