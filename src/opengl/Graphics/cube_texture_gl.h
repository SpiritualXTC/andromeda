#pragma once

#include <andromeda/Graphics/texture.h>

namespace andromeda
{
	namespace opengl
	{


		class TextureCubeGL : public CubeTexture
		{
		public:
			TextureCubeGL(UInt32 width, UInt32 height);
			virtual ~TextureCubeGL();


			const inline UInt32 width() const override { return _width; }
			const inline UInt32 height() const override { return _height; }


			void bind(UInt32 activeIndex) const override;
			void unbind(UInt32 activeIndex) const override;


			void resize(UInt32 width, UInt32 height) override;

			void data(CubeTextureFace face, const UInt8 * ptr) override;
			void data(CubeTextureFace face, const UInt8 * ptr, Int32 xOffset, Int32 yOffset, UInt32 width, UInt32 height) override;



		private:
			UInt32 _handle = 0;

			UInt32 _width = 0;
			UInt32 _height = 0;
		};
	}
}