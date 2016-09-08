#pragma once

#include <andromeda/Renderer/layer.h>

namespace andromeda
{
	class IFrameBuffer;
	class Camera;

	namespace deferred
	{
#if 0
		class DeferredLightingLayerExtension : public ILayerExtension
		{
		public:
			DeferredLightingLayerExtension(std::shared_ptr<IFrameBuffer> & fb);


			void begin(const std::shared_ptr<IShader> & shader) override;
			void end(const std::shared_ptr<IShader> & shader) override;


		private:
			std::shared_ptr<IFrameBuffer> _gBuffer;
		};
#endif



		class DeferredLightingEnvironment : public ILayerEnvironment
		{
		public:
			DeferredLightingEnvironment(const std::shared_ptr<IFrameBuffer> & fb, const std::shared_ptr<Camera> & worldCamera);

			void begin(const IShader * shader) override;
			void end(const IShader * shader) override;
		private:

			std::shared_ptr<IFrameBuffer> _gBuffer;
			std::shared_ptr<Camera> _camera;
		};

	}
}

