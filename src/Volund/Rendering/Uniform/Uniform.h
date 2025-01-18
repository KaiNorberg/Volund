#pragma once

#include "Math/Math.h"

#define VOLUND_TEMPLATE_UNIFORM_TYPES_ONLY typename = std::enable_if_t<std::is_same<T, IntUniformType>::value || std::is_same<T, FloatUniformType>::value || \
std::is_same<T, DoubleUniformType>::value || std::is_same<T, Vec2UniformType>::value || \
std::is_same<T, Vec3UniformType>::value || std::is_same<T, Vec4UniformType>::value || \
std::is_same<T, Mat4x4UniformType>::value || std::is_same<T, TextureUniformType>::value || \
std::is_same<T, FramebufferUniformType>::value>

namespace Volund
{
    class Shader;
    class Texture;
    class Framebuffer;

    using IntUniformType = int;
    using FloatUniformType = float;
    using DoubleUniformType = double;
    using Vec2UniformType = Vec2;
    using Vec3UniformType = Vec3;
    using Vec4UniformType = Vec4;
    //using UniformMat3x3 = Mat3x3;
    using Mat4x4UniformType = Mat4x4;
    using TextureUniformType = std::shared_ptr<Texture>;
    using FramebufferUniformType = std::shared_ptr<Framebuffer>;

    class PrimitiveUniform
    {
    public:

        template<typename T>
        bool Is() const;

        template<typename T>
        T& As();

        template<typename T>
        void Set(const T& value);

        std::string GetName() const;

        virtual uint64_t GetTypeId() const = 0;

        virtual void UpdateShader(std::shared_ptr<Shader> shader) = 0;

        PrimitiveUniform() = default;

        virtual ~PrimitiveUniform() = default;

    protected:

        std::string m_Name;

    private:
    };

    template<typename T, VOLUND_TEMPLATE_UNIFORM_TYPES_ONLY>
    class Uniform : public PrimitiveUniform
    {
    public:

        T& Get();

        void Set(const T& value);

        uint64_t GetTypeId() const override;

        void UpdateShader(std::shared_ptr<Shader> shader) override;

        static std::shared_ptr<Uniform<T>> Create(std::string const& name, const T& value);

    private:

        Uniform(std::string const& name, const T& value);

        T m_Value;
    };
}

#include "Uniform_Impl.h"

namespace Volund
{
    using IntUniform = Uniform<IntUniformType>;
    using FloatUniform = Uniform<FloatUniformType>;
    using DoubleUniform = Uniform<DoubleUniformType>;
    using Vec2Uniform = Uniform<Vec2UniformType>;
    using Vec3Uniform = Uniform<Vec3UniformType>;
    using Vec4Uniform = Uniform<Vec4UniformType>;
    using Mat4x4Uniform = Uniform<Mat4x4UniformType>;
    using TextureUniform = Uniform<TextureUniformType>;
    using FramebufferUniform = Uniform<FramebufferUniformType>;
}
