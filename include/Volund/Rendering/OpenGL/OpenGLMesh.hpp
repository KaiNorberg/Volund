#pragma once

#include "../Mesh.hpp"

namespace Volund
{
    class VOLUND_API OpenGLMesh : public Mesh
    {
    public:
        std::string GetFilepath() const override;
        AABB GetAABB(const Mat4x4& modelMatrix) const override;
        void Bind() override;
        void Unbind() override;
        void SetVertexBuffer(std::shared_ptr<VertexBuffer> buffer) override;
        void SetIndexBuffer(std::shared_ptr<IndexBuffer> buffer) override;
        std::shared_ptr<VertexBuffer> GetVertexBuffer() override;
        std::shared_ptr<IndexBuffer> GetIndexBuffer() override;
        const std::shared_ptr<VertexBuffer> GetVertexBuffer() const override;
        const std::shared_ptr<IndexBuffer> GetIndexBuffer() const override;
        OpenGLMesh(std::string const& filepath);
        OpenGLMesh(std::shared_ptr<VertexBuffer> VertexBuffer, std::shared_ptr<IndexBuffer> IndexBuffer);
        ~OpenGLMesh() override;
    private:
        uint32_t m_id;
        std::string m_filepath;
        std::shared_ptr<VertexBuffer> m_vertexBuffer;
        std::shared_ptr<IndexBuffer> m_indexBuffer;
    };
}