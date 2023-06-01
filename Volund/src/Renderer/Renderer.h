#pragma once

#include "Mesh/Mesh.h"
#include "Material/Material.h"
#include "RenderingAPI/RenderingAPI.h"

#include "UniformBuffer/UniformBuffer.h"

#include "Renderer/Framebuffer/Framebuffer.h"

#define VOLUND_UNIFORM_BUFFER_BINDING_CAMERA 0
#define VOLUND_UNIFORM_BUFFER_BINDING_LIGHTS 1
#define VOLUND_MAX_LIGHTS 64

#define VOLUND_UNIFORM_NAME_MODELMATRIX "_ModelMatrix"

namespace Volund
{
	class Renderer;

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
		Mat4x4 ViewMatrix;
		Mat4x4 ProjectionMatrix;

		Vec3 Position;

		uint16_t LayerMask; //Render if: ((model.LayerMask & eye.LayerMask) != 0

		Ref<Framebuffer> Target;
	};

	class RendererInstance
	{
	public:

		virtual void Begin() = 0;

		void Submit(const RendererModel& model);

		void Submit(const RendererLight& light);

		void Submit(const RendererEye& eye);

		virtual void End() = 0;

		RendererInstance();

		virtual ~RendererInstance() = default;

	protected:
		friend class Renderer;

		void UpdateLightUniforms();

		void UpdateCameraUniforms(const RendererEye& eye);

		struct Data
		{
			void Sort();

			void Discriminate(const RendererEye& eye);

			std::vector<RendererModel> Models;
			std::vector<RendererLight> Lights;
			std::vector<RendererEye> Eyes;
		} m_Data;

	private:

		Ref<UniformBuffer> m_CameraUniforms;
		Ref<UniformBuffer> m_LightsUniforms;
	};

	class Renderer
	{
	public:
		
		static void Init(Ref<RendererInstance> instance);

		static void Reset();

		static void Begin();

		static void Submit(const RendererModel& model);

		static void Submit(const RendererLight& light);

		static void Submit(const RendererEye& eye);

		static void End();

		Renderer() = delete;

	private:

		static inline Ref<RendererInstance> m_Instance;
	};
}

