#pragma once

#include "Shader.h"

namespace Volund
{
    class OpenGLShader : public Shader
    {
    public:

         void Use();

        /// <summary>
        /// Compiles and generates the shader, (Dont use if filepath was specified in the constructor).
        /// </summary>
         void Init(std::string const& FilePath) override;

        /// <summary>
        /// Sets a int shader uniform.
        /// </summary>
         void SetInt(int32_t Value, std::string const& Name) override;

        /// <summary>
        /// Sets a float shader uniform.
        /// </summary>
         void SetFloat(float Value, std::string const& Name) override;

        /// <summary>
        /// Sets a double shader uniform.
        /// </summary>
         void SetDouble(float Value, std::string const& Name) override;

        /// <summary>
        /// Sets a vector2 shader uniform.
        /// </summary>
         void SetVec2(Vec2 const& Value, std::string const& Name) override;

        /// <summary>
        /// Sets a vector3 shader uniform.
        /// </summary>
         void SetVec3(Vec3 const& Value, std::string const& Name) override;

        /// <summary>
        /// Sets a vector4 shader uniform.
        /// </summary>
         void SetVec4(Vec4 const& Value, std::string const& Name) override;

        /// <summary>
        /// Sets a matrix3 shader uniform.
        /// </summary>
         void SetMat3x3(Mat3x3 const& Value, std::string const& Name, bool Transpose = false) override;

        /// <summary>
        /// Sets a matrix4 shader uniform.
        /// </summary>
         void SetMat4x4(Mat4x4 const& Value, std::string const& Name, bool Transpose = false) override;

         OpenGLShader() = default;

         OpenGLShader(std::string const& FilePath);

         ~OpenGLShader();

    private:

        uint32_t GetUniformLocation(std::string const& Name);

        uint32_t CompileShader(uint32_t Type, std::string const& Source);

        std::unordered_map<std::string, uint32_t> UniformLocations;

        uint32_t ID = 0;
    };

} //namespace Volund