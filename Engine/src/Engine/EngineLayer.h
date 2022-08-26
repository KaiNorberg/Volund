#pragma once

namespace Volund
{
	class EngineLayer : public Layer
	{
	public:
		///////////////////////////////////////////////////////////////////////////

		VertexBuffer* VBuffer;
		IndexBuffer* IBuffer;

		uint32_t VertexArray;

		Shader* TestShader;

		///////////////////////////////////////////////////////////////////////////

		void LoadScene(std::string const& FilePath)
		{
			VOLUND_INFO("Loading Scene (%s)...", FilePath.c_str());

			if (this->_LoadedScene != nullptr)
			{
				delete this->_LoadedScene;
			}

			this->_LoadedScene = new Scene((std::filesystem::path)FilePath);
		}

		void OnAttach() override
		{
			JSON ConfigFile = JSON::Load(CONFIG_JSON);

			this->LoadScene(ConfigFile["Engine"]["MainScene"].GetAs<std::string>());

			///////////////////////////////////////////////////////////////////////////

			float Vertices[] =
			{
				-0.5f, -0.5, 0.0,    1.0, 0.0, 0.0, 1.0,
				 0.5,  -0.5, 0.0,    0.0, 1.0, 0.0, 1.0,
				 0.0,   0.5, 0.0,    0.0, 0.0, 1.0, 1.0
			};
			uint32_t Indices[] =
			{ 0, 1, 2 };

			TestShader = Shader::Create("Shaders/Test.shader");

			glGenVertexArrays(1, &VertexArray);			
			glBindVertexArray(VertexArray);

			VBuffer = VertexBuffer::Create(Vertices, sizeof(Vertices) / sizeof(float));

			VBuffer->SetLayout(
			{
				VertexAttributeType::OPENGL_FLOAT3,
				VertexAttributeType::OPENGL_FLOAT4
			});

			IBuffer = IndexBuffer::Create(Indices, sizeof(Indices) / sizeof(uint32_t));

			///////////////////////////////////////////////////////////////////////////
		}

		void OnDetach() override
		{			
			///////////////////////////////////////////////////////////////////////////

			if (TestShader != nullptr)
			{
				delete TestShader;
			}
			if (VBuffer != nullptr)
			{
				delete VBuffer;
			}
			if (IBuffer != nullptr)
			{
				delete IBuffer;
			}

			///////////////////////////////////////////////////////////////////////////

			if (_LoadedScene != nullptr)
			{
				delete _LoadedScene;
			}
		}

		void OnUpdate(TimeStep TS) override
		{		
			///////////////////////////////////////////////////////////////////////////

			glClearColor(0, 0, 0, 1);

			TestShader->Use();

			glBindVertexArray(VertexArray);
			glDrawElements(GL_TRIANGLES, IBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			///////////////////////////////////////////////////////////////////////////

			if (_LoadedScene != nullptr)
			{
				this->_LoadedScene->OnUpdate(TS);
			}
		}

	private:

		Scene* _LoadedScene = nullptr;
	};
}

