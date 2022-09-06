#include "PCH/PCH.h"
#include "MeshAsset.h"

#include "Scene/Scene.h"

#include "ModelLoader/ModelLoader.h"

namespace Volund
{
	Ref<Mesh> MeshAsset::Get()
	{
		return this->_Mesh;
	}

	MeshAsset::MeshAsset(AssetLibrary* Parent, std::string const& FilePath)
	{
		this->_FilePath = FilePath;

		ModelLoader<float, uint32_t> Loader = ModelLoader<float, uint32_t>(FilePath);

		Ref<VertexBuffer> VBuffer = VertexBuffer::Create(Loader.Vertices.data(), (uint32_t)Loader.Vertices.size());
		VBuffer->SetLayout({ VertexAttributeType::FLOAT3, VertexAttributeType::FLOAT2, VertexAttributeType::FLOAT3 });

		Ref<IndexBuffer> IBuffer = IndexBuffer::Create(Loader.Indices.data(), (uint32_t)Loader.Indices.size());

		this->_Mesh = Mesh::Create(VBuffer, IBuffer);
	}
}