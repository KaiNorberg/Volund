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

			TestShader = Shader::Create("Shaders/Test.shader");

			glGenVertexArrays(1, &VertexArray);			
			glBindVertexArray(VertexArray);

			float Vertices[9] =
			{
				-0.5f, -0.5, 0.0,
				0.5, -0.5, 0.0,
				0.0, 0.5, 0.0
			};
			uint32_t Indices[3] = 
			{ 0, 1, 2 };

			VBuffer = VertexBuffer::Create(Vertices, 9);
			IBuffer = IndexBuffer::Create(Indices, 3);		
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
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

