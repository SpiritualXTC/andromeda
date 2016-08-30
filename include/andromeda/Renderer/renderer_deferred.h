#pragma once

#include "renderer.h"

#include "render_stage.h"


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
		
		class DeferredGeometryStage;

		class DeferredLightingEnvironment;
		class DeferredLightingStage;
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


		std::shared_ptr<deferred::DeferredEnvironment> _geomEnvironment;
		std::shared_ptr<deferred::DeferredLightingEnvironment> _lightingEnvironment;


		std::shared_ptr<deferred::DeferredGeometryStage> _geometryStage;
		std::shared_ptr<deferred::DeferredLightingStage> _lightingStage;
	};
}