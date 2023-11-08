#pragma once

#include "Rendering/Mesh/Mesh.h"
#include "Rendering/Material/Material.h"
#include "Rendering/Effect/Effect.h"
#include "Rendering/RenderingAPI/RenderingAPI.h"
#include "Rendering/UniformBuffer/UniformBuffer.h"
#include "Rendering/Framebuffer/Framebuffer.h"
#include "Rendering/Uniform/Uniform.h"

#include "Scene/Scene.h"
#include "GameState/GameState.h"

#define VOLUND_UNIFORM_NAME_MODELMATRIX "_ModelMatrix"

namespace Volund
{
	struct RendererModel
	{
		Mat4x4 ModelMatrix;
		Ref<Mesh> ModelMesh;
		Ref<Material> Material;

		uint32_t LayerMask = 0xFFFFFFFF; //Render if: ((model.LayerMask & eye.LayerMask) != 0
	};

	struct RendererLight
	{
		RGB Color;
		float Brightness;
		Vec3 Position;
	};

	struct RendererEye
	{
		Mat4x4 ViewMatrix = Mat4x4();
		Mat4x4 ProjectionMatrix = Mat4x4();

		Ref<Framebuffer> Target;

		uint32_t LayerMask = 0xFFFFFFFF; //Render if: ((model.LayerMask & eye.LayerMask) != 0

		std::vector<Ref<Effect>> Effects;
	};

	class Renderer
	{
	public:

		virtual void Begin() = 0;

		void Submit(Ref<Scene> scene, Ref<Framebuffer> target);

		void Submit(Ref<GameState> gameState, Ref<Framebuffer> target);

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
		} m_Data;
	};
}

