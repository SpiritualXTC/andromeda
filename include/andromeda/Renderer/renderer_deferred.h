#pragma once

#include "renderer.h"

namespace andromeda
{
	class Camera;

	class IFrameBuffer;

	class Effect;

	class CubeTexture;

	/*
	
	*/
	class DeferredRenderer : public Renderer
	{
	public:
		DeferredRenderer(const std::shared_ptr<SceneGraph> & sg, const std::shared_ptr<Effect> & effect, const std::string & directionalTechnique);


		const std::shared_ptr<IFrameBuffer> getGBuffer() const { return _gBuffer; }



		void addDirectionalLight();


		// Set Environment Mapping
		inline void setEnvironmentReflectionmap(const std::shared_ptr<CubeTexture> & cubeTex) { _reflection = cubeTex; }


	protected:
		void onResize(Float width, Float height) override;
	//	void onBegin() override;
	//	void onEnd() override;

	private:
		std::shared_ptr<IFrameBuffer> _gBuffer;


		std::shared_ptr<CubeTexture> _reflection;



		class DeferredRendererLightingMethod;
		std::shared_ptr<DeferredRendererLightingMethod> _lightingMethod;
	};
}