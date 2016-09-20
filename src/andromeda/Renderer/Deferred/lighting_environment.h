#pragma once

#include <andromeda/Renderer/layer.h>

namespace andromeda
{
	class IFrameBuffer;
	class Camera;

	namespace deferred
	{
		class DeferredLightingEnvironment : public ILayerEnvironment
		{
		public:
			DeferredLightingEnvironment(const std::shared_ptr<IFrameBuffer> & fb, const std::shared_ptr<Camera> & worldCamera);

			void begin(GraphicsState & state) override;
			void end(GraphicsState & state) override;

		private:

			std::shared_ptr<IFrameBuffer> _gBuffer;
			std::shared_ptr<Camera> _camera;
		};

	}
}

