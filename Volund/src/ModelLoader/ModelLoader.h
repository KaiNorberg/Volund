#pragma once

#include "Filesystem/Filesystem.h"

#include "AABB/AABB.h"

namespace Volund
{
	template <typename V, typename I>
	class ModelLoader
	{
	public:
		
		std::vector<V> Vertices;
		std::vector<I> Indices;

		ModelLoader(const std::string& filepath);

	private:
		
		void LoadOBJ(const std::string& filepath);

		struct ArrayHasher
		{
			std::uint64_t operator()(const std::array<V, 8>& array) const
			{
				std::uint64_t h = 0;

				for (auto e : array)
				{
					h ^= std::hash<uint64_t>{}((uint64_t)(e)) + 0x9e3779b9 + (h << 6) + (h >> 2);
				}

				return h;
			}
		};
	};

	template <typename V, typename I>
	ModelLoader<V, I>::ModelLoader(const std::string& filepath)
	{
		if (filepath.ends_with(".obj") || filepath.ends_with(".vobj"))
		{
			this->LoadOBJ(filepath);
		}
		else
		{
			VOLUND_WARNING("Unable to read unknown model file type (%s)!", filepath.data());
		}
	}

	template <typename V, typename I>
	void ModelLoader<V, I>::LoadOBJ(const std::string& filepath)
	{
		std::vector<V> geometry;
		std::vector<V> textureCoords;
		std::vector<V> normals;

		std::unordered_map<std::array<V, 8>, I, ArrayHasher> vertexToIndexMap;

		auto stringStream = std::istringstream(Filesystem::Load(filepath));

		std::string line;
		while (std::getline(stringStream, line))
		{
			char lineHeader[16] = {};
			lineHeader[15] = 0;

			sscanf(line.c_str(), "%15s", lineHeader);

			if (strcmp(lineHeader, "v") == 0)
			{
				float x, y, z = 0.0f;
				VOLUND_ASSERT(sscanf(line.c_str(), "v %f %f %f", &x, &y, &z) == 3, "Unable to parse OBJ file (%s)!", filepath.data());

				geometry.push_back(x);
				geometry.push_back(y);
				geometry.push_back(z);
			}
			else if (strcmp(lineHeader, "vt") == 0)
			{
				float x, y = 0.0f;
				VOLUND_ASSERT(sscanf(line.c_str(), "vt %f %f", &x, &y) == 2, "Unable to parse OBJ file (%s)!", filepath.data());

				textureCoords.push_back(x);
				textureCoords.push_back(y);
			}
			else if (strcmp(lineHeader, "vn") == 0)
			{
				float x, y, z = 0.0f;
				VOLUND_ASSERT(sscanf(line.c_str(), "vn %f %f %f", &x, &y, &z) == 3, "Unable to parse OBJ file (%s)!", filepath.data());

				normals.push_back(x);
				normals.push_back(y);
				normals.push_back(z);
			}
			else if (strcmp(lineHeader, "f") == 0)
			{
				uint32_t geometryIndices[3];
				uint32_t textureCoordsIndices[3];
				uint32_t normalsIndices[3];

				VOLUND_ASSERT(sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", 
					&geometryIndices[0], &textureCoordsIndices[0], &normalsIndices[0],
					&geometryIndices[1], &textureCoordsIndices[1], &normalsIndices[1],
					&geometryIndices[2], &textureCoordsIndices[2], &normalsIndices[2]) == 9, "Unable to parse OBJ file (%s)!", filepath.data());

				for (uint64_t i = 0; i < 3; i++)
				{
					std::array<V, 8> vertex;

					if (!geometry.empty() && !textureCoords.empty() && !normals.empty())
					{
						const uint32_t geometryIndex = (geometryIndices[i] - 1) * 3;
						const uint32_t textureCoordsIndex = (textureCoordsIndices[i] - 1) * 2;
						const uint32_t normalsIndex = (normalsIndices[i] - 1) * 3;

						vertex =
						{
							geometry[geometryIndex + 0],
							geometry[geometryIndex + 1],
							geometry[geometryIndex + 2],
							textureCoords[textureCoordsIndex + 0],
							textureCoords[textureCoordsIndex + 1],
							normals[normalsIndex + 0],
							normals[normalsIndex + 1],
							normals[normalsIndex + 2]
						};
					}
					/*else if (!Geometry.empty() && TextureCoords.empty() && Normals.empty())
					{
						uint32_t GeometryIndex;
						VOLUND_ASSERT(sscanf(Line.c_str(), "f %d", &GeometryIndex) == 1, "Unable to parse OBJ file (%s)!", Filepath.data());
						GeometryIndex = (GeometryIndex - 1) * 3;

						Vertex =
						{
							Geometry[GeometryIndex + 0],
							Geometry[GeometryIndex + 1],
							Geometry[GeometryIndex + 2],
							0,
							0,
							0,
							0,
							0
						};
					}*/
					else
					{
						VOLUND_ERROR("Unable to parse OBJ file (%s)!", filepath.data());
					}

					if (vertexToIndexMap.contains(vertex))
					{
						this->Indices.push_back(vertexToIndexMap[vertex]);
					}
					else
					{
						this->Indices.push_back((uint32_t)(this->Vertices.size() / 8));

						for (uint64_t j = 0; j < 8; j++)
						{
							this->Vertices.push_back(vertex[j]);
						}
					}
				}
			}
			else
			{
				//Not implemented
			}
		}
	}
}
