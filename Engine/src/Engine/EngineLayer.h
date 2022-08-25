#pragma once

namespace Volund
{
	class EngineLayer : public Layer
	{
	public:
		///////////////////////////////////////////////////////////////////////////

		uint32_t VertexArray;

		uint32_t VertexBuffer;

		uint32_t IndexBuffer;

		OpenGLShader TestShader;

		///////////////////////////////////////////////////////////////////////////

		void LoadScene(std::string const& FilePath)
		{
			VOLUND_CLIENT_INFO("Loading scene (%s)...", FilePath.c_str());

			if (this->_LoadedScene != nullptr)
			{
				delete this->_LoadedScene;
			}

			this->_LoadedScene = new Scene((std::filesystem::path)FilePath);
		}

		void OnAttach() override
		{
			JSON ConfigFile = LoadJSON(CONFIG_JSON);

			if (ConfigFile.contains("Misc") && ConfigFile["Misc"].contains("MainScene"))
			{
				this->LoadScene(ConfigFile["Misc"]["MainScene"].get<std::string>());
			}
			else
			{
				VOLUND_CLIENT_ERROR("Config file does not define a MainScene");
			}		

			///////////////////////////////////////////////////////////////////////////

			TestShader.Init("Shaders/Test.shader");

			glGenVertexArrays(1, &VertexArray);			
			glBindVertexArray(VertexArray);

			glGenBuffers(1, &VertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);

			float Verticies[9] =
			{
				-0.5f, -0.5, 0.0,
				0.5, -0.5, 0.0,
				0.0, 0.5, 0.0
			};

			glBufferData(GL_ARRAY_BUFFER, sizeof(Verticies), Verticies, GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

			glGenBuffers(1, &IndexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);

			uint32_t Indices[3] = { 0, 1, 2 };
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);			
			
			///////////////////////////////////////////////////////////////////////////
		}

		void OnDetach() override
		{
			if (_LoadedScene != nullptr)
			{
				delete _LoadedScene;
			}
		}

		void OnUpdate(TimeStep TS) override
		{		
			///////////////////////////////////////////////////////////////////////////

			glClearColor(0, 0, 0, 1);

			TestShader.Use();

			glBindVertexArray(VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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

