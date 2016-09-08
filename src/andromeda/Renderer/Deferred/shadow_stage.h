#pragma once

#include <andromeda/Renderer/render_stage.h>



#include <andromeda/Graphics/frame_buffer.h>	//TODO: TEMP

namespace andromeda
{

	
	class IFrameBuffer;

	class Camera;
	class LightDirectional;



	namespace deferred
	{


		/*
			TODO:
			This is a basic trial implementation

			
		*/
		class DeferredShadowStage : public RenderStage
		{
		public:
			DeferredShadowStage(const std::shared_ptr<Camera> & camera);
			virtual ~DeferredShadowStage();

			void begin(GraphicsState & gs) override;
			void end(GraphicsState & gs) override;


			inline std::shared_ptr<ITexture> getShadowMap() { return _shadowMap->getDepthTexture(); }

			// Sets the Light
		//	inline void setLight(const std::shared_ptr<LightDirectional> & light)
		//	{
		//		_light = light;
		//	}


		private:

		//	std::shared_ptr<LightDirectional> _light;

			std::shared_ptr<IFrameBuffer> _shadowMap;
		};
	}
}