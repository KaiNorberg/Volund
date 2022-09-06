#pragma once

#include "Shader.h"

namespace Volund
{
    class OpenGLShader : public Shader
    {
    public:

        void Bind();

        /// <summary>
        /// Returns if the shader has the specified uniform.
        /// </summary>
        bool HasUniform(std::string const& Name) override;

        /// <summary>
        /// Sets a int shader uniform.
        /// </summary>
        void SetInt(std::string const& Name, int32_t Value) override;

        /// <summary>
        /// Sets a float shader uniform.
        /// </summary>
        void SetFloat(std::string const& Name, float Value) override;

        /// <summary>
        /// Sets a double shader uniform.
        /// </summary>
        void SetDouble(std::string const& Name, float Value) override;

        /// <summary>
        /// Sets a vector2 shader uniform.
        /// </summary>
        void SetVec2(std::string const& Name, Vec2 const& Value) override;

        /// <summary>
        /// Sets a vector3 shader uniform.
        /// </summary>
        void SetVec3(std::string const& Name, Vec3 const& Value) override;

        /// <summary>
        /// Sets a vector4 shader uniform.
        /// </summary>
        void SetVec4(std::string const& Name, Vec4 const& Value) override;

        /// <summary>
        /// Sets a matrix3 shader uniform.
        /// </summary>
        void SetMat3x3(std::string const& Name, Mat3x3 const& Value, bool Transpose = false) override;

        /// <summary>
        /// Sets a matrix4 shader uniform.
        /// </summary>
        void SetMat4x4(std::string const& Name, Mat4x4 const& Value, bool Transpose = false) override;

        OpenGLShader() = default;

        OpenGLShader(std::string const& FilePath);

        ~OpenGLShader();

    private:

        uint32_t CompileShader(uint32_t Type, std::string const& Source);

        uint32_t GetUniformLocation(std::string const& Name);

        std::unordered_map<std::string, uint32_t> UniformLocations;

        uint32_t ID = 0;
    };

} //namespace Volund