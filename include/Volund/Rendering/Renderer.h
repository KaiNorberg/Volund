#pragma once

#include "Mesh.h"
#include "Material.h"
#include "Effect.h"
#include "RenderingAPI.h"
#include "Framebuffer.h"
#include "Uniform.h"

#include "../Scene.h"

#define VOLUND_UNIFORM_NAME_MODELMATRIX "_ModelMatrix"

namespace Volund
{
    struct RendererModel
    {
        Mat4x4 ModelMatrix;
        std::shared_ptr<Mesh> mesh;
        std::shared_ptr<Material> material;
        uint32_t LayerMask = 0xFFFFFFFF; //Render if: ((model.LayerMask & eye.LayerMask) != 0
    };

    struct RendererLight
    {
        RGB Color;
        float Brightness;
        Vec3 pos;
    };

    struct RendererEye
    {
        Mat4x4 ViewMatrix = Mat4x4();
        Mat4x4 ProjectionMatrix = Mat4x4();
        std::shared_ptr<Framebuffer> Target;
        uint32_t LayerMask = 0xFFFFFFFF; //Render if: ((model.LayerMask & eye.LayerMask) != 0
        std::vector<std::shared_ptr<Effect>> Effects;
    };

    class VOLUND_API Renderer
    {
    public:
        virtual void Begin() = 0;
        void Submit(std::shared_ptr<Scene> scene, std::shared_ptr<Framebuffer> target);
        void Submit(const RendererModel& model);
        void Submit(const RendererLight& light);
        void Submit(const RendererEye& eye);
        virtual void End() = 0;
        virtual ~Renderer() = default;
    protected:
        struct Data
        {
            std::vector<RendererModel> Models;
            std::vector<RendererEye> Eyes;
            std::vector<RendererLight> Lights;
        } m_data;
    };
}