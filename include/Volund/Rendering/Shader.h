#pragma once

#include "Texture.h"
#include "Framebuffer.h"
#include "Uniform.h"

#include "../ResourceLibrary/ResourceLibrary.h"

#include "MaterialBlueprint.h"

#include "../ShaderLoader.h"

namespace Volund
{
    class Shader
    {
    public:

        virtual void Bind() = 0;

        virtual bool HasUniform(std::string const& name) = 0;

        virtual uint32_t GetId() = 0;

        virtual void SetInt(std::string const& name, IntUniformType value) = 0;
        virtual void SetFloat(std::string const& name, FloatUniformType value) = 0;
        virtual void SetDouble(std::string const& name, DoubleUniformType value) = 0;
        virtual void SetVec2(std::string const& name, const Vec2UniformType& value) = 0;
        virtual void SetVec3(std::string const& name, const Vec3UniformType& value) = 0;
        virtual void SetVec4(std::string const& name, const Vec4UniformType& value) = 0;
        //virtual void SetMat3x3(std::string const& name, const UniformMat3x3& value, bool transpose = false) = 0;
        virtual void SetMat4x4(std::string const& name, const Mat4x4UniformType& value, bool transpose = false) = 0;
        virtual void SetTexture(std::string const& name, const TextureUniformType& value) = 0;
        virtual void SetFramebuffer(std::string const& name, const FramebufferUniformType& value) = 0;

        virtual void Init(const ShaderSource& source, std::shared_ptr<MaterialBlueprint> materialBlueprint) = 0;

        virtual const std::shared_ptr<MaterialBlueprint> GetMaterialBlueprint() = 0;

        static std::shared_ptr<Shader> Create();

        static std::shared_ptr<Shader> Create(std::string const& filepath);

        static std::shared_ptr<Shader> Create(const ShaderSource& source, std::shared_ptr<MaterialBlueprint> materialBlueprint);

        virtual ~Shader() = default;

    };
}