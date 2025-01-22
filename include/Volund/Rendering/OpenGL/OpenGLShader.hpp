#pragma once

#include "../Shader.hpp"

namespace Volund
{
    class VOLUND_API OpenGLShader : public Shader
    {
    public:
        void Bind() override;
        uint32_t GetId() const override;
        bool HasUniform(std::string const& name) override;
        void SetInt(std::string const& name, int value) override;
        void SetFloat(std::string const& name, float value) override;
        void SetDouble(std::string const& name, double value) override;
        void SetVec2(std::string const& name, const Vec2& value) override;
        void SetVec3(std::string const& name, const Vec3& value) override;
        void SetVec4(std::string const& name, const Vec4& value) override;
        //void SetMat3x3(std::string const& name, const Mat3x3& value, bool transpose = false) override;
        void SetMat4x4(std::string const& name, const Mat4x4& value, bool transpose = false) override;
        void SetTexture(std::string const& name, const std::shared_ptr<Texture>& value) override;
        void SetFramebuffer(std::string const& name, const std::shared_ptr<Framebuffer>& value) override;
        const std::shared_ptr<MaterialBlueprint> GetMaterialBlueprint() const override;
        std::string GetFilepath() const override;
        OpenGLShader(const std::string& filepath);
        ~OpenGLShader() override;
    private:
        uint32_t CompileShader(uint32_t type, std::string const& source);
        uint32_t GetUniformLocation(std::string const& name);
        std::unordered_map<std::string, uint32_t> m_uniformLocations;
        uint32_t m_id = 0;
        int32_t m_nextTextureUnit = 0;
        int32_t m_maxTextureUnit = 0;
        std::string m_filepath;
        std::shared_ptr<MaterialBlueprint> m_materialBlueprint;
    };
} //namespace Volund