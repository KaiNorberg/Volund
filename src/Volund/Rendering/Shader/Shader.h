#pragma once

#include "Rendering/Texture/Texture.h"
#include "Rendering/Framebuffer/Framebuffer.h"
#include "Rendering/Uniform/Uniform.h"

#include "ResourceLibrary/ResourceLibrary.h"

#include "MaterialBlueprint/MaterialBlueprint.h"

#include "ShaderLoader/ShaderLoader.h"

namespace Volund
{
    class Shader
    {
    public:

        virtual void Bind() = 0;

        virtual bool HasUniform(const std::string& name) = 0;

        virtual uint32_t GetId() = 0;

        virtual void SetInt(const std::string& name, IntUniformType value) = 0;
        virtual void SetFloat(const std::string& name, FloatUniformType value) = 0;
        virtual void SetDouble(const std::string& name, DoubleUniformType value) = 0;
        virtual void SetVec2(const std::string& name, const Vec2UniformType& value) = 0;
        virtual void SetVec3(const std::string& name, const Vec3UniformType& value) = 0;
        virtual void SetVec4(const std::string& name, const Vec4UniformType& value) = 0;
        //virtual void SetMat3x3(const std::string& name, const UniformMat3x3& value, bool transpose = false) = 0;
        virtual void SetMat4x4(const std::string& name, const Mat4x4UniformType& value, bool transpose = false) = 0;
        virtual void SetTexture(const std::string& name, const TextureUniformType& value) = 0;
        virtual void SetFramebuffer(const std::string& name, const FramebufferUniformType& value) = 0;

        virtual void Init(const ShaderSource& source, std::shared_ptr<MaterialBlueprint> materialBlueprint) = 0;

        virtual const std::shared_ptr<MaterialBlueprint> GetMaterialBlueprint() = 0;

        static std::shared_ptr<Shader> Create();

        static std::shared_ptr<Shader> Create(const std::string& filepath);

        static std::shared_ptr<Shader> Create(const ShaderSource& source, std::shared_ptr<MaterialBlueprint> materialBlueprint);

        virtual ~Shader() = default;

    };
}
