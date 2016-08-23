#pragma once

#include <andromeda/Renderer/renderer.h>

namespace andromeda
{
	class IFrameBuffer;

	namespace deferred
	{
		class DeferredRendererGeometryMethod : public RendererMethod
		{
		public:
			DeferredRendererGeometryMethod(const std::shared_ptr<IFrameBuffer> & gBuffer, const std::shared_ptr<ILayerEnvironment> & enviro);


			void begin() override;
			void end() override;

		private:
			std::shared_ptr<IFrameBuffer> _gBuffer;
		};
	}
}