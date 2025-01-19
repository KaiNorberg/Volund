#include "Lua/LuaAPI.h"

#include "Component/Components.h"

namespace Volund
{
    void LuaAPI::Bind(LuaState* state)
    {
        state->m_state.open_libraries(sol::lib::base);

        state->m_state.set_function("require", [state](std::string const& filepath) {
            return state->m_state.script_file(state->AbsolutePath(filepath));
        });

        state->m_state.set_function("print", [state](std::string const& string) {
            VOLUND_INFO(string.c_str());
        });

        state->m_state.new_usertype<Vec2>("Vec2", 
            sol::constructors<Vec2(), Vec2(float), Vec2(float, float)>(),
            "x", &Vec2::x,
            "y", &Vec2::y,
            "length", &Vec2::Length,
            "length2", &Vec2::Length2,
            "operator+", sol::overload(
                [](const Vec2& a, const Vec2& b) { return a + b; },
                [](const Vec2& a, float b) { return a + b; }
            ),
            "operator-", sol::overload(
                [](const Vec2& a, const Vec2& b) { return a - b; },
                [](const Vec2& a, float b) { return a - b; }
            ),
            "operator*", sol::overload(
                [](const Vec2& a, const Vec2& b) { return a * b; },
                [](const Vec2& a, float b) { return a * b; }
            ),
            "operator/", sol::overload(
                [](const Vec2& a, const Vec2& b) { return a / b; },
                [](const Vec2& a, float b) { return a / b; }
            ),
            "operator[]", [](Vec2& v, uint8_t index) { return v[index]; }
        );

        state->m_state.new_usertype<Vec3>("Vec3", 
            sol::constructors<Vec3(), Vec3(float), Vec3(float, float, float)>(),
            "x", &Vec3::x,
            "y", &Vec3::y,
            "z", &Vec3::z,
            "length", &Vec3::Length,
            "length2", &Vec3::Length2,
            "operator+", sol::overload(
                [](const Vec3& a, const Vec3& b) { return a + b; },
                [](const Vec3& a, float b) { return a + b; }
            ),
            "operator-", sol::overload(
                [](const Vec3& a, const Vec3& b) { return a - b; },
                [](const Vec3& a, float b) { return a - b; }
            ),
            "operator*", sol::overload(
                [](const Vec3& a, const Vec3& b) { return a * b; },
                [](const Vec3& a, float b) { return a * b; }
            ),
            "operator/", sol::overload(
                [](const Vec3& a, const Vec3& b) { return a / b; },
                [](const Vec3& a, float b) { return a / b; }
            ),
            "operator[]", [](Vec3& v, uint8_t index) { return v[index]; }
        );

        state->m_state.new_usertype<Vec4>("Vec4", 
            sol::constructors<Vec4(), Vec4(float), Vec4(float, float, float, float)>(),
            "x", &Vec4::x,
            "y", &Vec4::y,
            "z", &Vec4::z,
            "w", &Vec4::w,
            "length", &Vec4::Length,
            "length2", &Vec4::Length2,
            "operator+", sol::overload(
                [](const Vec4& a, const Vec4& b) { return a + b; },
                [](const Vec4& a, float b) { return a + b; }
            ),
            "operator-", sol::overload(
                [](const Vec4& a, const Vec4& b) { return a - b; },
                [](const Vec4& a, float b) { return a - b; }
            ),
            "operator*", sol::overload(
                [](const Vec4& a, const Vec4& b) { return a * b; },
                [](const Vec4& a, float b) { return a * b; }
            ),
            "operator/", sol::overload(
                [](const Vec4& a, const Vec4& b) { return a / b; },
                [](const Vec4& a, float b) { return a / b; }
            ),
            "operator[]", [](Vec4& v, uint8_t index) { return v[index]; }
        );

        state->m_state.new_usertype<Mat4x4>("Mat4x4", 
            sol::constructors<
                Mat4x4(), 
                Mat4x4(float), 
                Mat4x4(const Vec4&, const Vec4&, const Vec4&, const Vec4&),
                Mat4x4(const std::array<float, 16>&)
            >(),
            "operator+", sol::overload(
                [](const Mat4x4& a, const Mat4x4& b) { return a + b; },
                [](const Mat4x4& a, float b) { return a + b; }
            ),
            "operator-", sol::overload(
                [](const Mat4x4& a, const Mat4x4& b) { return a - b; },
                [](const Mat4x4& a, float b) { return a - b; }
            ),
            "operator*", sol::overload(
                [](const Mat4x4& a, const Mat4x4& b) { return a * b; },
                [](const Mat4x4& a, float b) { return a * b; },
                [](const Mat4x4& a, const Vec4& v) { return a * v; },
                [](const Mat4x4& a, const Vec3& v) { return a * v; }
            ),
            "operator[]", [](Mat4x4& m, uint8_t index) { return m[index]; }
        );

        state->m_state.new_usertype<Shader>("Shader", sol::constructors<>(),
            "new", [state](std::string const& filepath) { return Shader::Create(state->AbsolutePath(filepath)); },
            "has_uniform", &Shader::HasUniform,
            "get_id", &Shader::GetId,
            "set_int", &Shader::SetInt,
            "set_float", &Shader::SetFloat,
            "set_double", &Shader::SetDouble,
            "set_vec2", &Shader::SetVec2,
            "set_vec3", &Shader::SetVec3,
            "set_vec4", &Shader::SetVec4,
            "set_mat4x4", &Shader::SetMat4x4,
            "set_texture", &Shader::SetTexture,
            "set_framebuffer", &Shader::SetFramebuffer
        );

        state->m_state.new_usertype<Texture>("Texture", 
            "new", sol::overload(
                [state](std::string const& filepath) { return Texture::Create(state->AbsolutePath(filepath)); },
                [](uint32_t width, uint32_t height, sol::table imageData) 
                {
                    std::vector<unsigned char> pixels;
                    for (auto& [key, value] : imageData) 
                    {
                        pixels.push_back(value.as<unsigned char>());
                    }

                    return Texture::Create(pixels.data(), width, height);
                }
            ),
            "get_id", &Texture::GetID,
            "get_width", &Texture::GetWidth,
            "get_height", &Texture::GetHeight,
            "bind", sol::overload(
                [](std::shared_ptr<Texture> texture) { texture->Bind(); },
                [](std::shared_ptr<Texture> texture, uint32_t unit) { texture->Bind(unit); }
            ),
            "set_data", [](std::shared_ptr<Texture> texture, uint32_t width, uint32_t height, sol::table imageData) 
            {
                std::vector<unsigned char> pixels;
                for (auto& [key, value] : imageData) 
                {
                    pixels.push_back(value.as<unsigned char>());
                }

                texture->SetData(pixels.data(), width, height);
            }
        );

        state->m_state.new_usertype<Mesh>("Mesh", sol::constructors<>(),
            "new", [state](std::string const& filepath) { return Mesh::Create(state->AbsolutePath(filepath)); }
        );

        state->m_state.new_usertype<Material>("Material", sol::constructors<>(),
            "new", [](std::shared_ptr<Shader> shader) { return Material::Create(shader); },
            "set_shader", &Material::SetShader,
            "get_shader", &Material::GetShader,
            "contains_int", [](std::shared_ptr<Material> material, std::string const& name) 
            { 
                return material->Contains<IntUniformType>(name); 
            },
            "contains_float", [](std::shared_ptr<Material> material, std::string const& name) 
            { 
                return material->Contains<FloatUniformType>(name); 
            },
            "contains_vec2", [](std::shared_ptr<Material> material, std::string const& name) 
            { 
                return material->Contains<Vec2UniformType>(name); 
            },
            "contains_vec3", [](std::shared_ptr<Material> material, std::string const& name) 
            { 
                return material->Contains<Vec3UniformType>(name); 
            },
            "contains_vec4", [](std::shared_ptr<Material> material, std::string const& name) 
            { 
                return material->Contains<Vec4UniformType>(name); 
            },
            "contains_mat4x4", [](std::shared_ptr<Material> material, std::string const& name) 
            { 
                return material->Contains<Mat4x4UniformType>(name); 
            },
            "contains_texture", [](std::shared_ptr<Material> material, std::string const& name) 
            { 
                return material->Contains<TextureUniformType>(name); 
            },
            "contains_framebuffer", [](std::shared_ptr<Material> material, std::string const& name) 
            { 
                return material->Contains<FramebufferUniformType>(name); 
            },
            "set_int", [](std::shared_ptr<Material> material, std::string const& name, IntUniformType value)
            {
                material->Set(name, value);
            },
            "set_float", [](std::shared_ptr<Material> material, std::string const& name, FloatUniformType value)
            {
                material->Set(name, value);
            },
            "set_double", [](std::shared_ptr<Material> material, std::string const& name, DoubleUniformType value)
            {
                material->Set(name, value);
            },
            "set_vec2", [](std::shared_ptr<Material> material, std::string const& name, Vec2UniformType value)
            {
                material->Set(name, value);
            },
            "set_vec3", [](std::shared_ptr<Material> material, std::string const& name, Vec3UniformType value)
            {
                material->Set(name, value);
            },
            "set_vec4", [](std::shared_ptr<Material> material, std::string const& name, Vec4UniformType value)
            {
                material->Set(name, value);
            },
            "set_mat4x4", [](std::shared_ptr<Material> material, std::string const& name, Mat4x4UniformType value)
            {
                material->Set(name, value);
            },
            "set_texture", [](std::shared_ptr<Material> material, std::string const& name, TextureUniformType value)
            {
                material->Set(name, value);
            },
            "set_framebuffer", [](std::shared_ptr<Material> material, std::string const& name, FramebufferUniformType value)
            {
                material->Set(name, value);
            }
        );
        
        state->m_state.new_usertype<AudioBuffer>("AudioBuffer", sol::constructors<AudioBuffer(std::string const&)>());

        state->m_state.new_usertype<Camera>("Camera", 
            sol::constructors<Camera()>(),
            "fov", &Camera::FOV,
            "nearPlane", &Camera::NearPlane,
            "farPlane", &Camera::FarPlane,
            "set_layer_mask", &Camera::SetLayerMask,
            "get_layer_mask", &Camera::GetLayerMask,
            "get_view_matrix", &Camera::GetViewMatrix,
            "get_origin_view_matrix", &Camera::GetOriginViewMatrix,
            "get_projection_matrix", &Camera::GetProjectionMatrix
        );

        state->m_state.new_usertype<Transform>("Transform", 
            sol::constructors<Transform(Vec3, Vec3, Vec3)>(),
            "pos", &Transform::pos,
            "scale", &Transform::scale,
            "set_rotation", &Transform::SetRotation,
            "get_rotation", &Transform::GetRotation,
            "add_rotation", &Transform::AddRotation,
            "get_front", &Transform::GetFront,
            "get_right", &Transform::GetRight,
            "get_up", &Transform::GetUp,
            "get_model_matrix", &Transform::GetModelMatrix
        );

        state->m_state.new_usertype<PointLight>("PointLight", 
            sol::constructors<PointLight(Vec3, float)>(),
            "color", &PointLight::color,
            "brightness", &PointLight::brightness
        );

        state->m_state.new_usertype<MeshRenderer>("MeshRenderer", 
            sol::constructors<MeshRenderer(std::shared_ptr<Mesh>, std::shared_ptr<Material>)>(),
            "is_valid", &MeshRenderer::IsValid,
            "set_layer", &MeshRenderer::SetLayer,
            "get_layer_mask", &MeshRenderer::GetLayerMask,
            "set_mesh", &MeshRenderer::SetMesh,
            "set_material", &MeshRenderer::SetMaterial,
            "get_mesh", &MeshRenderer::GetMesh,
            "get_material", &MeshRenderer::GetMaterial
        );

        state->m_state.new_usertype<CameraMovement>("CameraMovement", 
            sol::constructors<CameraMovement(float, float)>(),
            "speed", &CameraMovement::speed,
            "sensitivity", &CameraMovement::sensitivity
        );

        state->m_state.new_usertype<SoundSource>("SoundSource", 
            sol::constructors<SoundSource(std::shared_ptr<AudioBuffer>)>(),
            "autoPlay", &SoundSource::AutoPlay,
            "play", &SoundSource::Play,
            "set_buffer", &SoundSource::SetBuffer,
            "get_buffer", &SoundSource::GetBuffer,
            "set_pitch", &SoundSource::SetPitch,
            "get_pitch", &SoundSource::GetPitch,
            "set_looping", &SoundSource::SetLooping,
            "get_looping", &SoundSource::GetLooping,
            "set_gain", &SoundSource::SetGain,
            "get_gain", &SoundSource::GetGain
        );

        state->m_state.new_usertype<Tag>("Tag", 
            sol::constructors<Tag(std::string)>(),
            "string", &Tag::string
        );

        state->m_state.new_usertype<Entity>("Entity");

        state->m_state.new_usertype<Scene>("Scene", sol::constructors<Scene()>(),
            "new", []() { return std::make_shared<Scene>(); },
            "register", &Scene::Register,
            "unregister", &Scene::Unregister,
            "is_registered", &Scene::IsRegistered,

            // Add Component Methods
            "add_camera", [](std::shared_ptr<Scene> scene, Entity entity)
            {
                return scene->AddComponent<Camera>(entity);
            },
            "add_mesh_renderer", [](std::shared_ptr<Scene> scene, Entity entity, std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material)
            {
                return scene->AddComponent<MeshRenderer>(entity, mesh, material);
            },
            "add_point_light", [](std::shared_ptr<Scene> scene, Entity entity)
            {
                return scene->AddComponent<PointLight>(entity);
            },            
            "add_transform", [](std::shared_ptr<Scene> scene, Entity entity, Vec3 pos, Vec3 rotation, Vec3 scale)
            {
                return scene->AddComponent<Transform>(entity, pos, rotation, scale);
            },
            "add_camera_movement", [](std::shared_ptr<Scene> scene, Entity entity, float speed = 1.0f, float sensitivity = 1.0f)
            {
                return scene->AddComponent<CameraMovement>(entity, speed, sensitivity);
            },
            "add_sound_listener", [](std::shared_ptr<Scene> scene, Entity entity)
            {
                return scene->AddComponent<SoundListener>(entity);
            },
            "add_sound_source", [](std::shared_ptr<Scene> scene, Entity entity, std::shared_ptr<AudioBuffer> buffer)
            {
                return scene->AddComponent<SoundSource>(entity, buffer);
            },
            "add_tag", [](std::shared_ptr<Scene> scene, Entity entity, std::string const& tag)
            {
                return scene->AddComponent<Tag>(entity, tag);
            },
            /*"add_script", [state](std::shared_ptr<Scene> scene, Entity entity, std::string const& tag)
            {
                return scene->AddComponent<Tag>(entity, tag);
            },*/

            // Remove Component Methods
            "remove_camera", [](std::shared_ptr<Scene> scene, Entity entity, uint64_t index = 0)
            {
                scene->RemoveComponent<Camera>(entity, index);
            },
            "remove_mesh_renderer", [](std::shared_ptr<Scene> scene, Entity entity, uint64_t index = 0)
            {
                scene->RemoveComponent<MeshRenderer>(entity, index);
            },
            "remove_point_light", [](std::shared_ptr<Scene> scene, Entity entity, uint64_t index = 0)
            {
                scene->RemoveComponent<PointLight>(entity, index);
            },
            "remove_transform", [](std::shared_ptr<Scene> scene, Entity entity, uint64_t index = 0)
            {
                scene->RemoveComponent<Transform>(entity, index);
            },
            "remove_camera_movement", [](std::shared_ptr<Scene> scene, Entity entity, uint64_t index = 0)
            {
                scene->RemoveComponent<CameraMovement>(entity, index);
            },
            "remove_sound_listener", [](std::shared_ptr<Scene> scene, Entity entity, uint64_t index = 0)
            {
                scene->RemoveComponent<SoundListener>(entity, index);
            },
            "remove_sound_source", [](std::shared_ptr<Scene> scene, Entity entity, uint64_t index = 0)
            {
                scene->RemoveComponent<SoundSource>(entity, index);
            },
            "remove_tag", [](std::shared_ptr<Scene> scene, Entity entity, uint64_t index = 0)
            {
                scene->RemoveComponent<Tag>(entity, index);
            },

            // Has Component Methods
            "has_camera", [](std::shared_ptr<Scene> scene, Entity entity, uint64_t index = 0)
            {
                return scene->HasComponent<Camera>(entity, index);
            },
            "has_mesh_renderer", [](std::shared_ptr<Scene> scene, Entity entity, uint64_t index = 0)
            {
                return scene->HasComponent<MeshRenderer>(entity, index);
            },
            "has_point_light", [](std::shared_ptr<Scene> scene, Entity entity, uint64_t index = 0)
            {
                return scene->HasComponent<PointLight>(entity, index);
            },
            "has_transform", [](std::shared_ptr<Scene> scene, Entity entity, uint64_t index = 0)
            {
                return scene->HasComponent<Transform>(entity, index);
            },
            "has_camera_movement", [](std::shared_ptr<Scene> scene, Entity entity, uint64_t index = 0)
            {
                return scene->HasComponent<CameraMovement>(entity, index);
            },
            "has_sound_listener", [](std::shared_ptr<Scene> scene, Entity entity, uint64_t index = 0)
            {
                return scene->HasComponent<SoundListener>(entity, index);
            },
            "has_sound_source", [](std::shared_ptr<Scene> scene, Entity entity, uint64_t index = 0)
            {
                return scene->HasComponent<SoundSource>(entity, index);
            },
            "has_tag", [](std::shared_ptr<Scene> scene, Entity entity, uint64_t index = 0)
            {
                return scene->HasComponent<Tag>(entity, index);
            },

            // Component Amount Methods
            "camera_amount", [](std::shared_ptr<Scene> scene, Entity entity)
            {
                return scene->ComponentAmount<Camera>(entity);
            },
            "mesh_renderer_amount", [](std::shared_ptr<Scene> scene, Entity entity)
            {
                return scene->ComponentAmount<MeshRenderer>(entity);
            },
            "point_light_amount", [](std::shared_ptr<Scene> scene, Entity entity)
            {
                return scene->ComponentAmount<PointLight>(entity);
            },
            "transform_amount", [](std::shared_ptr<Scene> scene, Entity entity)
            {
                return scene->ComponentAmount<Transform>(entity);
            },
            "camera_movement_amount", [](std::shared_ptr<Scene> scene, Entity entity)
            {
                return scene->ComponentAmount<CameraMovement>(entity);
            },
            "sound_listener_amount", [](std::shared_ptr<Scene> scene, Entity entity)
            {
                return scene->ComponentAmount<SoundListener>(entity);
            },
            "sound_source_amount", [](std::shared_ptr<Scene> scene, Entity entity)
            {
                return scene->ComponentAmount<SoundSource>(entity);
            },
            "tag_amount", [](std::shared_ptr<Scene> scene, Entity entity)
            {
                return scene->ComponentAmount<Tag>(entity);
            },

            // Get Component Methods
            "get_camera", [](std::shared_ptr<Scene> scene, Entity entity, uint64_t index = 0)
            {
                return scene->GetComponent<Camera>(entity, index);
            },
            "get_mesh_renderer", [](std::shared_ptr<Scene> scene, Entity entity, uint64_t index = 0)
            {
                return scene->GetComponent<MeshRenderer>(entity, index);
            },
            "get_point_light", [](std::shared_ptr<Scene> scene, Entity entity, uint64_t index = 0)
            {
                return scene->GetComponent<PointLight>(entity, index);
            },
            "get_transform", [](std::shared_ptr<Scene> scene, Entity entity, uint64_t index = 0)
            {
                return scene->GetComponent<Transform>(entity, index);
            },
            "get_camera_movement", [](std::shared_ptr<Scene> scene, Entity entity, uint64_t index = 0)
            {
                return scene->GetComponent<CameraMovement>(entity, index);
            },
            "get_sound_listener", [](std::shared_ptr<Scene> scene, Entity entity, uint64_t index = 0)
            {
                return scene->GetComponent<SoundListener>(entity, index);
            },
            "get_sound_source", [](std::shared_ptr<Scene> scene, Entity entity, uint64_t index = 0)
            {
                return scene->GetComponent<SoundSource>(entity, index);
            },
            "get_tag", [](std::shared_ptr<Scene> scene, Entity entity, uint64_t index = 0)
            {
                return scene->GetComponent<Tag>(entity, index);
            }
        );
    }
}