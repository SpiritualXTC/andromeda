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
			DeferredRendererGeometryMethod(std::shared_ptr<IFrameBuffer> & gBuffer);


			void begin() override;
			void end() override;

		private:
			std::shared_ptr<IFrameBuffer> _gBuffer;
		};
	}
}