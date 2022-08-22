#pragma once

namespace Volund
{
	class EngineLayer : public Layer
	{
	public:

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
		}

		void OnDetach() override
		{
			if (_LoadedScene != nullptr)
			{
				delete _LoadedScene;
			}
		}

		void OnUpdate() override
		{
			if (_LoadedScene != nullptr)
			{
				this->_LoadedScene->OnUpdate();
			}
		}

	private:

		Scene* _LoadedScene = nullptr;
	};
}

