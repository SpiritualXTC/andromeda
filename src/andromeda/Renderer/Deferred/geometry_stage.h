#pragma once

#include <andromeda/Renderer/render_stage.h>

namespace andromeda
{
	class IFrameBuffer;

	class Camera;

	namespace deferred
	{
		class DeferredGeometryStage : public RenderStage
		{
		public:
			DeferredGeometryStage(const std::shared_ptr<IFrameBuffer> & gBuffer, const std::shared_ptr<Camera> & camera = nullptr, const std::shared_ptr<ILayerEnvironment> & enviro = nullptr);


			void begin(GraphicsState & gs) override;
			void end(GraphicsState & gs) override;

		private:
			std::shared_ptr<IFrameBuffer> _gBuffer;
		};
	}
}