#pragma once

#include "Falcor.h"

namespace GModDXR
{
	using namespace Falcor;

	struct WorldData
	{
		uint32_t length;
		std::vector<float3> pPositions;
		std::vector<float3> pNormals;
		float3 sunDirection;
	};

	class Renderer : public IRenderer
	{
	public:
		void onLoad(RenderContext* pRenderContext) override;
		void onFrameRender(RenderContext* pRenderContext, const Fbo::SharedPtr& pTargetFbo) override;
		void onResizeSwapChain(uint32_t width, uint32_t height) override;
		bool onKeyEvent(const KeyboardEvent& keyEvent) override;
		bool onMouseEvent(const MouseEvent& mouseEvent) override;
		void onGuiRender(Gui* pGui) override;

		void setWorldData(const WorldData* data);
		void setCameraDefaults(const float3 pos, const float3 up);

	private:
		SceneBuilder::SharedPtr pBuilder;
		Scene::SharedPtr pScene;

		RtProgram::SharedPtr pRaytraceProgram = nullptr;

		Camera::SharedPtr pCamera;
		float3 cameraStartPos;
		float3 cameraStartUp;

		bool useDOF = false;
		RtProgramVars::SharedPtr pRtVars;
		Texture::SharedPtr pRtOut;

		uint32_t sampleIndex = 0xdeadbeef;

		const WorldData* pWorldData;

		float zNear = 0.01f;
		float zFar = 100.f;

		void setPerFrameVars(const Fbo* pTargetFbo);
		void renderRT(RenderContext* pContext, const Fbo* pTargetFbo);
		void loadScene(const Fbo* pTargetFbo);
	};
}