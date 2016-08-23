#pragma once

#include "renderer.h"

namespace andromeda
{
	class Camera;

	class IFrameBuffer;

	class Effect;

	class CubeTexture;


	

	// Forward Declaration
	namespace deferred
	{
		class DeferredEnvironment;
		class DeferredRendererLightingMethod;
	}



	/*
	
	*/
	class DeferredRenderer : public Renderer
	{
	public:
		DeferredRenderer(const std::shared_ptr<SceneGraph> & sg, const std::shared_ptr<Effect> & effect, const std::string & directionalTechnique);


		const std::shared_ptr<IFrameBuffer> getGBuffer() const { return _gBuffer; }


		// Add a Direction Light
		void addDirectionalLight();

		// Set Environment Mapping
		void setEnvironmentReflectionmap(const std::shared_ptr<CubeTexture> & cubeTex);

	protected:
		void onResize(Float width, Float height) override;
	//	void onBegin() override;
	//	void onEnd() override;

	private:
		std::shared_ptr<IFrameBuffer> _gBuffer;

		std::shared_ptr<deferred::DeferredEnvironment> _environment;

		
		std::shared_ptr<deferred::DeferredRendererLightingMethod> _lightingMethod;
	};
}