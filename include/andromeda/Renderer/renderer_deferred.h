#pragma once

#include "renderer.h"

#include "render_stage.h"




namespace andromeda
{
	class Camera;

	class ITexture;
	class IFrameBuffer;

	class Effect;

	class CubeTexture;

	class LightDirectional;

	

	// Forward Declaration
	namespace deferred
	{
		class DeferredEnvironment;		// Rename to DeferredGeometryEnvironment
		class DeferredGeometryStage;	
		
		class DeferredShadowStage;

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
		void addDirectionalLight(const std::shared_ptr<LightDirectional> & directional);

		// Set Environment Mapping :: This will also need to support dynamic environment mapping.
		void setEnvironmentReflectionMap(const std::shared_ptr<CubeTexture> & cubeTex);




		// TEMP
		std::shared_ptr<ITexture> getShadowMap();


	protected:
		void onResize(Float width, Float height) override;
	//	void onBegin() override;
	//	void onEnd() override;

	private:
		std::shared_ptr<IFrameBuffer> _gBuffer;


		std::shared_ptr<deferred::DeferredEnvironment> _geomEnvironment;
		std::shared_ptr<deferred::DeferredLightingEnvironment> _lightingEnvironment;

		

		std::shared_ptr<deferred::DeferredGeometryStage> _geometryStage;

		std::shared_ptr<deferred::DeferredShadowStage> _shadowStage;	// Typically there will be numerous shadow stages.... depending on the number of lights, but this is a test!

		std::shared_ptr<deferred::DeferredLightingStage> _lightingStage;
	};
}