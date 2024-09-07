#pragma once

#include "Rendering/IndexBuffer/IndexBuffer.h"
#include "Rendering/VertexBuffer/VertexBuffer.h"

#include "AABB/AABB.h"

#include "ResourceLibrary/ResourceLibrary.h"

namespace Volund
{
    class Mesh
    {
    public:

        virtual AABB GetAABB(const Mat4x4& modelMatrix) = 0;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetVertexBuffer(Ref<VertexBuffer> buffer) = 0;
        virtual void SetIndexBuffer(Ref<IndexBuffer> buffer) = 0;

        virtual Ref<VertexBuffer> GetVertexBuffer() = 0;
        virtual Ref<IndexBuffer> GetIndexBuffer() = 0;

        virtual const Ref<VertexBuffer> GetVertexBuffer() const = 0;
        virtual const Ref<IndexBuffer> GetIndexBuffer() const = 0;

        static Ref<Mesh> Create();

        static Ref<Mesh> Create(Ref<VertexBuffer> vertexBuffer, Ref<IndexBuffer> indexBuffer);

        virtual ~Mesh() = default;
    };
}
