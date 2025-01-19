#pragma once

#include "../Mesh.h"

namespace Volund
{
    class OpenGLMesh : public Mesh
    {
    public:
        AABB GetAABB(const Mat4x4& modelMatrix) override;
        void Bind() const override;
        void Unbind() const override;
        void SetVertexBuffer(std::shared_ptr<VertexBuffer> buffer) override;
        void SetIndexBuffer(std::shared_ptr<IndexBuffer> buffer) override;
        std::shared_ptr<VertexBuffer> GetVertexBuffer() override;
        std::shared_ptr<IndexBuffer> GetIndexBuffer() override;
        const std::shared_ptr<VertexBuffer> GetVertexBuffer() const override;
        const std::shared_ptr<IndexBuffer> GetIndexBuffer() const override;
        OpenGLMesh();
        OpenGLMesh(std::shared_ptr<VertexBuffer> VertexBuffer, std::shared_ptr<IndexBuffer> IndexBuffer);
        ~OpenGLMesh() override;
    private:
        uint32_t m_id;
        std::shared_ptr<VertexBuffer> m_vertexBuffer;
        std::shared_ptr<IndexBuffer> m_indexBuffer;
    };
}