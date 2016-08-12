#pragma once

#include <andromeda/Renderer/layer.h>

namespace andromeda
{
	class IFrameBuffer;

	namespace deferred
	{
		class DeferredGBufferLayerExtension : public ILayerExtension
		{
		public:
			DeferredGBufferLayerExtension(std::shared_ptr<IFrameBuffer> & fb);


			void begin(const std::shared_ptr<IShader> & shader) override;
			void end(const std::shared_ptr<IShader> & shader) override;


		private:
			std::shared_ptr<IFrameBuffer> _gBuffer;
		};

	}
}

