#pragma once

#include "IndexBuffer.h"
#include "VertexBuffer.h"

#include "../AABB.h"

#include "../ResourceLibrary/ResourceLibrary.h"

namespace Volund
{
    class Mesh
    {
    public:
        virtual std::string GetFilepath() const = 0;
        virtual AABB GetAABB(const Mat4x4& modelMatrix) const = 0;
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual void SetVertexBuffer(std::shared_ptr<VertexBuffer> buffer) = 0;
        virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer> buffer) = 0;
        virtual std::shared_ptr<VertexBuffer> GetVertexBuffer() = 0;
        virtual std::shared_ptr<IndexBuffer> GetIndexBuffer() = 0;
        virtual const std::shared_ptr<VertexBuffer> GetVertexBuffer() const = 0;
        virtual const std::shared_ptr<IndexBuffer> GetIndexBuffer() const = 0;
        static std::shared_ptr<Mesh> Create();
        static std::shared_ptr<Mesh> Create(std::string const& filepath);
        static std::shared_ptr<Mesh> Create(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer);
        virtual ~Mesh() = default;
    };
}