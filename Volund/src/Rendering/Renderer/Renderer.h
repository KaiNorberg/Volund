#pragma once

#include "Rendering/Mesh/Mesh.h"
#include "Rendering/Material/Material.h"
#include "Rendering/RenderingAPI/RenderingAPI.h"
#include "Rendering/UniformBuffer/UniformBuffer.h"
#include "Rendering/Framebuffer/Framebuffer.h"

#include "Scene/Scene.h"

#define VOLUND_UNIFORM_BUFFER_BINDING_CAMERA 0
#define VOLUND_UNIFORM_BUFFER_BINDING_LIGHTS 1
#define VOLUND_MAX_LIGHTS 64

#define VOLUND_UNIFORM_NAME_MODELMATRIX "_ModelMatrix"

namespace Volund
{
	struct RendererModel
	{
		Mat4x4 ModelMatrix;
		Ref<Mesh> mesh;
		Ref<Material> material;

		uint16_t LayerMask; //Render if: ((model.LayerMask & eye.LayerMask) != 0

		bool Discriminated = false;
	};

	struct RendererLight
	{
		RGB Color;
		Vec3 Position;
		float Brightness;
	};

	struct RendererEye
	{
		Mat4x4 ViewMatrix = Mat4x4();
		Mat4x4 ProjectionMatrix = Mat4x4() ;

		Vec3 Position = Vec3();

		uint16_t LayerMask; //Render if: ((model.LayerMask & eye.LayerMask) != 0

		Ref<Framebuffer> Target;
	};

	class Renderer
	{
	public:

		virtual void Begin(Ref<Framebuffer> defaultBuffer) = 0;

		void Submit(Ref<Scene> scene);

		void Submit(const RendererModel& model);

		void Submit(const RendererLight& light);

		void Submit(const RendererEye& eye);

		virtual void End() = 0;

		Renderer();

		virtual ~Renderer() = default;

	protected:

		void UpdateLightUniforms();

		void UpdateCameraUniforms(const RendererEye& eye);

		struct Data
		{
			void Sort();

			void Discriminate(const RendererEye& eye);

			Ref<Framebuffer> DefaultBuffer;

			std::vector<RendererModel> Models;
			std::vector<RendererLight> Lights;
			std::vector<RendererEye> Eyes;
		} m_Data;

	private:

		Ref<UniformBuffer> m_CameraUniforms;
		Ref<UniformBuffer> m_LightsUniforms;
	};
}

