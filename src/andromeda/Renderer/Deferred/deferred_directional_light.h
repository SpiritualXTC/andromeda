#pragma once

#include <andromeda/Renderer/renderable.h>

namespace andromeda
{
	class Geometry;


	namespace deferred
	{
		/*
		This class needs to be using an interface to abstract directional lights
		*/
		class DeferredRendererDirectionalLight : public IRenderable
		{
		public:
			DeferredRendererDirectionalLight();



			void render(const std::shared_ptr<IShader> shader, MatrixStack & ms) override;

		private:
			// These attributes need to be stored somewhere where the application can gain direct access to them...
			// For Real-time lighting adjustments...
			// This will do for now, however :)
			glm::vec3 _lightDirection;
			glm::vec3 _lightDiffuse;

			std::shared_ptr<Geometry> _geometry;
		};
	}
}