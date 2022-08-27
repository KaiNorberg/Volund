#include "PCH/PCH.h"

#include "GameLayer.h"

namespace Volund
{
	void GameLayer::LoadScene(std::string const& FilePath)
	{
		VOLUND_INFO("Loading Scene (%s)...", FilePath.c_str());

		this->_LoadedScene.reset(new Scene((std::filesystem::path)FilePath));
	}

	void GameLayer::OnAttach()
	{
		JSON ConfigFile = JSON::Load(VOLUND_CONFIG_JSON);

		this->LoadScene(ConfigFile["Engine"]["MainScene"].GetAs<std::string>());

		float Vertices[] =
		{
			-0.5f, -0.5, 0.0,    1.0, 0.0, 0.0, 1.0,
			 0.5,  -0.5, 0.0,    0.0, 1.0, 0.0, 1.0,
			 0.0,   0.5, 0.0,    0.0, 0.0, 1.0, 1.0
		};
		uint32_t Indices[] = { 0, 1, 2 };

		_TestShader.reset(Shader::Create("Shaders/Test.shader"));

		Ref<VertexBuffer> VBuffer = Ref<VertexBuffer>(VertexBuffer::Create(Vertices, sizeof(Vertices) / sizeof(float)));
		Ref<IndexBuffer> IBuffer = Ref<IndexBuffer>(IndexBuffer::Create(Indices, sizeof(Indices) / sizeof(uint32_t)));
		VBuffer->SetLayout({ VertexAttributeType::OPENGL_FLOAT3, VertexAttributeType::OPENGL_FLOAT4 });

		this->_VertexArray.reset(VertexArray::Create(VBuffer, IBuffer));
	}

	void GameLayer::OnDetach()
	{

	}

	void GameLayer::OnUpdate(TimeStep TS)
	{
		_TestShader->Use();

		_VertexArray->Bind();
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

		if (_LoadedScene != nullptr)
		{
			this->_LoadedScene->OnUpdate(TS);
		}
	}
}