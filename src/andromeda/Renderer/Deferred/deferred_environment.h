#pragma once

#include <andromeda/Renderer/layer.h>

namespace andromeda
{
	class CubeTexture;

	namespace deferred
	{
		class DeferredEnvironment : public ILayerEnvironment
		{
		public:
			DeferredEnvironment();
			virtual ~DeferredEnvironment();

			void begin(const IShader * shader) override;
			void end(const IShader * shader) override;



			void setEnvironmentReflectionmap(const std::shared_ptr<CubeTexture> & cubeTex) { _enviromentReflection = cubeTex; }

		private:
			std::shared_ptr<CubeTexture> _enviromentReflection;
		};
	}
}
