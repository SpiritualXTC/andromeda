#pragma once

#include <andromeda/Renderer/render_stage.h>



#include <andromeda/Graphics/frame_buffer.h>	//TODO: TEMP

namespace andromeda
{

	
	class IFrameBuffer;

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
			DeferredShadowStage();
			virtual ~DeferredShadowStage();

			void begin() override;
			void end() override;


			inline std::shared_ptr<ITexture> getShadowMap() { return _shadowMap->getDepthTexture(); }

			inline void setLight(const std::shared_ptr<LightDirectional> & light)
			{
				_light = light;
			}


		private:

			std::shared_ptr<LightDirectional> _light;

			std::shared_ptr<IFrameBuffer> _shadowMap;
		};
	}
}