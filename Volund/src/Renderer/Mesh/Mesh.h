#pragma once

#include "Renderer/Indexbuffer/Indexbuffer.h"
#include "Renderer/Vertexbuffer/Vertexbuffer.h"

#include "AABB/AABB.h"

namespace Volund
{
	class Mesh
	{
	public:

		AABB GetAABB(const Mat4x4& modelMatrix);

		std::string GetFilepath();

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetVertexbuffer(Ref<Vertexbuffer>& buffer) = 0;
		virtual void SetIndexbuffer(Ref<Indexbuffer>& buffer) = 0;

		Ref<Vertexbuffer> GetVertexbuffer();
		Ref<Indexbuffer> GetIndexbuffer();
		const Ref<Vertexbuffer> GetVertexbuffer() const;
		const Ref<Indexbuffer> GetIndexbuffer() const;

		static Ref<Mesh> Create(const std::string& filepath);

		static Ref<Mesh> Create();

		static Ref<Mesh> Create(Ref<Vertexbuffer>& vertexbuffer, Ref<Indexbuffer>& indexbuffer);

		virtual ~Mesh() = default;

	protected:

		AABB m_Aabb = {};

		std::string m_Filepath;

		Ref<Vertexbuffer> m_Vertexbuffer;
		Ref<Indexbuffer> m_Indexbuffer;
	};
}
