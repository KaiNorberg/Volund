#pragma once

#include "Renderer/IndexBuffer/IndexBuffer.h"
#include "Renderer/VertexBuffer/VertexBuffer.h"

#include "Time/Time.h"

namespace Volund
{
	template<typename V, typename I>
	class ModelLoader
	{
	public:

		std::vector<V> Vertices;
		std::vector<I> Indices;

		ModelLoader(std::string const& FilePath);

	private:

		void LoadOBJ(std::string const& FilePath);

		struct ArrayHasher 
		{
			std::size_t operator()(const std::array<V, 8>& Array) const 
			{
				std::size_t H = 0;

				for (auto E : Array) 
				{
					H ^= std::hash<int>{}((size_t)(E))+0x9e3779b9 + (H << 6) + (H >> 2);
				}

				return H;
			}
		};
	};

	template<typename V, typename I>
	inline ModelLoader<V, I>::ModelLoader(std::string const& FilePath)
	{
		VOLUND_INFO("Loading OBJ file (%s)...", FilePath.c_str());

		Timer T;

		if (FilePath.ends_with(".obj"))
		{
			this->LoadOBJ(FilePath);
		}
		else
		{
			VOLUND_WARNING("Unable to read unknown model file type (%s)!", FilePath.c_str());
		}
	}

	template<typename V, typename I>
	inline void ModelLoader<V, I>::LoadOBJ(std::string const& FilePath)
	{
		std::vector<V> Geometry;
		std::vector<V> TextureCoords;
		std::vector<V> Normals;

		std::unordered_map<std::array<V, 8>, uint32_t, ArrayHasher> VertexToIndexMap;

		FILE* File = fopen(FilePath.c_str(), "r");

		if (File == nullptr)
		{
			VOLUND_ERROR("Unable to open OBJ file (%s)!", FilePath.c_str());
		}

		while (true)
		{
			char LineHeader[16] = {};
			LineHeader[15] = 0;

			int RET = fscanf(File, "%15s", LineHeader);
			if (RET == EOF || RET == NULL)
			{
				break;
			}

			if (strcmp(LineHeader, "v") == 0)
			{
				float X, Y, Z = 0.0f;
				VOLUND_ASSERT(fscanf(File, "%f %f %f\n", &X, &Y, &Z) == 3, "Unable to parse OBJ file (%s)!", FilePath.c_str());

				Geometry.push_back(X);
				Geometry.push_back(Y);
				Geometry.push_back(Z);
			}
			else if (strcmp(LineHeader, "vt") == 0)
			{
				float X, Y = 0.0f;
				VOLUND_ASSERT(fscanf(File, "%f %f\n", &X, &Y) == 2, "Unable to parse OBJ file (%s)!", FilePath.c_str());

				TextureCoords.push_back(X);
				TextureCoords.push_back(Y);
			}
			else if (strcmp(LineHeader, "vn") == 0)
			{
				float X, Y, Z = 0.0f;
				VOLUND_ASSERT(fscanf(File, "%f %f %f\n", &X, &Y, &Z) == 3, "Unable to parse OBJ file (%s)!", FilePath.c_str());

				Normals.push_back(X);
				Normals.push_back(Y);
				Normals.push_back(Z);
			}
			else if (strcmp(LineHeader, "f") == 0)
			{
				for (int i = 0; i < 3; i++)
				{
					std::array<V, 8> Vertex;

					if (!Geometry.empty() && !TextureCoords.empty() && !Normals.empty())
					{
						int GeometryIndex, TextureCoordsIndex, NormalsIndex;
						VOLUND_ASSERT(fscanf(File, "%d/%d/%d", &GeometryIndex, &TextureCoordsIndex, &NormalsIndex) == 3, "Unable to parse OBJ file (%s)!", FilePath.c_str());
						GeometryIndex = (GeometryIndex - 1) * 3;
						TextureCoordsIndex = (TextureCoordsIndex - 1) * 2;
						NormalsIndex = (NormalsIndex - 1) * 3;

						Vertex =
						{
							Geometry[GeometryIndex + 0],
							Geometry[GeometryIndex + 1],
							Geometry[GeometryIndex + 2],
							TextureCoords[TextureCoordsIndex + 0],
							TextureCoords[TextureCoordsIndex + 1],
							Normals[NormalsIndex + 0],
							Normals[NormalsIndex + 1],
							Normals[NormalsIndex + 2]
						};
					}
					else if (!Geometry.empty() && TextureCoords.empty() && Normals.empty())
					{
						int GeometryIndex;
						VOLUND_ASSERT(fscanf(File, "%d", &GeometryIndex) == 1, "Unable to parse OBJ file (%s)!", FilePath.c_str());
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
					}
					else
					{
						VOLUND_ERROR("Unable to parse OBJ file (%s)!", FilePath.c_str());
					}

					if (VertexToIndexMap.contains(Vertex))
					{
						this->Indices.push_back(VertexToIndexMap[Vertex]);
					}
					else
					{
						this->Indices.push_back((uint32_t)(this->Vertices.size() / 8));

						for (int i = 0; i < 8; i++)
						{
							this->Vertices.push_back(Vertex[i]);
						}
					}
				}
			} 
			else
			{
				//Not implemented
			}
		}

		fclose(File);
	}
}

