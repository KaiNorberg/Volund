#pragma once

#include "Renderer/Indexbuffer/Indexbuffer.h"
#include "Renderer/Vertexbuffer/Vertexbuffer.h"

namespace Volund
{
	class Mesh
	{
	public:

		std::string GetFilepath();

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetVertexbuffer(Ref<Vertexbuffer>& Buffer) = 0;
		virtual void SetIndexbuffer(Ref<Indexbuffer>& Buffer) = 0;

		Ref<Vertexbuffer> GetVertexbuffer();
		Ref<Indexbuffer> GetIndexbuffer();
		const Ref<Vertexbuffer> GetVertexbuffer() const;
		const Ref<Indexbuffer> GetIndexbuffer() const;

		static Ref<Mesh> Create(std::string_view Filepath);

		static Ref<Mesh> Create(Ref<Vertexbuffer>& VBuffer, Ref<Indexbuffer>& IBuffer);

		virtual ~Mesh() = default;

	protected:

		std::string _Filepath;

		Ref<Vertexbuffer> _Vertexbuffer;
		Ref<Indexbuffer> _Indexbuffer;
	};
}
