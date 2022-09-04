#pragma once

namespace Volund
{
    /// <summary>
    /// A shader object that Contains code that describes how to render a mesh to the screen.
    /// </summary>
    class Shader
    {
    public:

        virtual void Bind() = 0;

        /// <summary>
        /// Compiles and generates the shader, (Dont use if filepath was specified in the constructor).
        /// </summary>
        virtual void Init(std::string const& FilePath) = 0;

        /// <summary>
        /// Returns if the shader has the specified uniform.
        /// </summary>
        virtual bool HasUniform(std::string const& Name) = 0;

        /// <summary>
        /// Sets a int shader uniform.
        /// </summary>
        virtual void SetInt(std::string const& Name, int32_t Value) = 0;

        /// <summary>
        /// Sets a float shader uniform.
        /// </summary>
        virtual void SetFloat(std::string const& Name, float Value) = 0;

        /// <summary>
        /// Sets a double shader uniform.
        /// </summary>
        virtual void SetDouble(std::string const& Name, float Value) = 0;

        /// <summary>
        /// Sets a vector2 shader uniform.
        /// </summary>
        virtual void SetVec2(std::string const& Name, Vec2 const& Value) = 0;

        /// <summary>
        /// Sets a vector3 shader uniform.
        /// </summary>
        virtual void SetVec3(std::string const& Name, Vec3 const& Value) = 0;

        /// <summary>
        /// Sets a vector4 shader uniform.
        /// </summary>
        virtual void SetVec4(std::string const& Name, Vec4 const& Value) = 0;

        /// <summary>
        /// Sets a matrix3 shader uniform.
        /// </summary>
        virtual void SetMat3x3(std::string const& Name, Mat3x3 const& Value, bool Transpose = false) = 0;

        /// <summary>
        /// Sets a matrix4 shader uniform.
        /// </summary>
        virtual void SetMat4x4(std::string const& Name, Mat4x4 const& Value, bool Transpose = false) = 0;

        static Ref<Shader> Create(std::string const& FilePath);

        virtual ~Shader() = default;

    protected:

        struct Source
        {
            std::string VertexSource;

            std::string FragmentSource;

            std::string GeometrySource;
        };

        Source ParseShader(std::string const& FilePath);
    };

} //namespace Volund