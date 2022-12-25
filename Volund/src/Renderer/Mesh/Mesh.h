#pragma once

#include "Renderer/Indexbuffer/Indexbuffer.h"
#include "Renderer/Vertexbuffer/Vertexbuffer.h"

#include "AABB/AABB.h"

namespace Volund
{
	class Mesh
	{
	public:

		AABB GetAABB(const Mat4x4& ModelMatrix);

		std::string GetFilepath();

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetVertexbuffer(Ref<Vertexbuffer>& Buffer) = 0;
		virtual void SetIndexbuffer(Ref<Indexbuffer>& Buffer) = 0;

		Ref<Vertexbuffer> GetVertexbuffer();
		Ref<Indexbuffer> GetIndexbuffer();
		const Ref<Vertexbuffer> GetVertexbuffer() const;
		const Ref<Indexbuffer> GetIndexbuffer() const;

		static Ref<Mesh> Create(const std::string& Filepath);

		static Ref<Mesh> Create();

		static Ref<Mesh> Create(Ref<Vertexbuffer>& VBuffer, Ref<Indexbuffer>& IBuffer);

		virtual ~Mesh() = default;

	protected:

		AABB _AABB;

		std::string _Filepath;

		Ref<Vertexbuffer> _Vertexbuffer;
		Ref<Indexbuffer> _Indexbuffer;
	};
}
