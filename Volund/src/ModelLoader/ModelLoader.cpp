#include "PCH/PCH.h"
#include "ModelLoader.h"

#include "Math/Math.h"

namespace Volund
{
	void ModelLoader::LoadFile(const std::string& filepath)
	{
		std::ifstream file(filepath);

		if (!file)
		{
			VOLUND_WARNING("Unable to load mesh file (%s)!", filepath.c_str());
		}

		std::stringstream stringStream;
		stringStream << file.rdbuf();

		if (filepath.ends_with(".obj") || filepath.ends_with(".vobj"))
		{
			this->ParseOBJ(stringStream.str());
		}
		else
		{
			VOLUND_WARNING("Unable to read unknown model file type (%s)!", filepath.data());
		}
	}

	bool ModelLoader::Valid()
	{
		return this->m_Valid;
	}

	int f = 0;

	void ModelLoader::ParseOBJ(const std::string& content)
	{
		this->m_Valid = true;

		std::vector<Vec3> geometry;
		std::vector<Vec3> normals;
		std::vector<Vec2> textureCoords;

		struct ArrayHasher
		{
			std::uint64_t operator()(const std::array<float, 8>& array) const
			{
				std::uint64_t h = 0;
				for (auto e : array)
				{
					h ^= std::hash<uint64_t>{}((uint64_t)(e)) + 0x9e3779b9 + (h << 6) + (h >> 2);
				}
				return h;
			}
		};
		std::unordered_map<std::array<float, 8>, uint32_t, ArrayHasher> indexMap;

		std::stringstream stringStream;
		stringStream << content;
		std::string line;
		int x = 0;
		while (std::getline(stringStream, line))
		{
			auto words = Utils::SplitString(line, ' ');

			if (words.empty() || words[0].empty())
			{
				continue;
			}

			switch (words[0][0])
			{
			case 'v':
			{
				if (words[0] == "v") //Is vertex
				{
					if (words.size() == 4)
					{
						geometry.emplace_back(Utils::Svtof(words[1]), Utils::Svtof(words[2]), Utils::Svtof(words[3]));
					}
					else
					{
						VOLUND_WARNING("Corrupt vertex detected in .obj file!");
						this->m_Valid = false;
					}
				}
				else if (words[0] == "vt") //Is texturecoord
				{
					if (words.size() == 3)
					{
						textureCoords.emplace_back(Utils::Svtof(words[1]), Utils::Svtof(words[2]));
					}
					else
					{
						VOLUND_WARNING("Corrupt texture coord detected in .obj file!");
						this->m_Valid = false;
					}
				}
				else if (words[0] == "vn") //Is normal
				{
					if (words.size() == 4)
					{
						normals.emplace_back(Utils::Svtof(words[1]), Utils::Svtof(words[2]), Utils::Svtof(words[3]));
					}
					else
					{
						VOLUND_WARNING("Corrupt texture coord detected in .obj file!");
						this->m_Valid = false;
					}
				}
			}
			break;
			case 'f': //Is face
			{
				if (words.size() == 4)
				{
					for (int i = 1; i < 4; i++)
					{
						auto vertexIndicies = Utils::SplitString(words[i], '/');

						int gIndex = Utils::Svtoi(vertexIndicies[0]);
						int tIndex = Utils::Svtoi(vertexIndicies[1]);
						int nIndex = Utils::Svtoi(vertexIndicies[2]);

						Vec3 g = geometry[gIndex - 1];
						Vec2 t = textureCoords[tIndex - 1];
						Vec3 n = normals[nIndex - 1];

						std::array<float, 8> vertex = { g.x, g.y, g.z, t.x, t.y, n.x, n.y, n.z };

						if (indexMap.contains(vertex))
						{
							this->Indices.push_back(indexMap[vertex]);
						}
						else
						{
							this->Indices.push_back((uint32_t)(this->Vertices.size() / 8));
							for (auto& scalar : vertex)
							{
								this->Vertices.push_back(scalar);
							}
						}
					}						
				}
				else
				{
					VOLUND_WARNING("Corrupt face detected in .obj file!");
					this->m_Valid = false;
				}
			}
			break;
			default:
			{

			}
			break;
			}
		}
	}
}
