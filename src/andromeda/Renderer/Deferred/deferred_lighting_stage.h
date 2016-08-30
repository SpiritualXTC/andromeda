#pragma once

#include <andromeda/Renderer/render_stage.h>

namespace andromeda
{
	class Effect;
	class IFrameBuffer;
	class IRenderable;
	class ILayerEnvironment;

	namespace deferred
	{
		




		class  DeferredLightingStage : public RenderStage
		{
		public:
			DeferredLightingStage(const std::shared_ptr<ILayerEnvironment> & enviro,
				const std::shared_ptr<Effect> & effect, const std::string & directionalTechnique);


			void begin() override {}

			void end() override {}




			/*

			*/
			void addDirectionalLight();


		private:
			std::shared_ptr<RenderableGroup> _directionalLights;

			std::shared_ptr<IRenderable> _renderable;
		};

	}
}