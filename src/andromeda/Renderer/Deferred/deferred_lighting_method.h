#pragma once

#include <andromeda/Renderer/renderer.h>

namespace andromeda
{
	class Effect;
	class IFrameBuffer;
	class IRenderable;

	namespace deferred
	{
		class  DeferredRendererLightingMethod : public RendererMethod
		{
		public:
			DeferredRendererLightingMethod(std::shared_ptr<IFrameBuffer> & gBuffer, 
				const std::shared_ptr<Effect> & effect, const std::string & directionalTechnique);


			void begin() override {}

			void end() override {}




			/*

			*/
			void addDirectionalLight();


		private:
			std::shared_ptr<IFrameBuffer> _gBuffer;

			std::shared_ptr<Camera> _directionalCamera;
			std::shared_ptr<RenderableGroup> _directionalLights;

			std::shared_ptr<IRenderable> _renderable;
		};

	}
}