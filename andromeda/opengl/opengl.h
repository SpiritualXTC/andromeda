#pragma once

#include <shared/graphics.h>

namespace andromeda
{
	namespace opengl
	{
		class OpenGL : public IGraphics
		{
		public:
			OpenGL();
			virtual ~OpenGL();


			// Setters / Getters
			Boolean setClearColor(Float r, Float g, Float b) override;

			// Methods
			Boolean clear(ClearMaskBits mask) override;

			std::shared_ptr<IGraphicsFactory> getFactory() override;

		private:
			std::shared_ptr<IGraphicsFactory> _factory;
		};


	}
}