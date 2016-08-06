#pragma once

#include <andromeda/Graphics/texture.h>

namespace andromeda
{
	namespace opengl
	{
		/*
			OpenGL Implementation of a texture
		*/
		class TextureGL : public Texture
		{
		public:
			TextureGL(UInt32 width, UInt32 height);
			virtual ~TextureGL();

			const inline UInt32 width() const override { return _width; }
			const inline UInt32 height() const override { return _height; }




			void bind(UInt32 activeIndex) const override;
			void unbind(UInt32 activeIndex) const override;



			void resize(const UInt8 * ptr, UInt32 width, UInt32 height) override;

			void data(const UInt8 * ptr) override;
			void data(const UInt8 * ptr, Int32 xOffset, Int32 yOffset, UInt32 width, UInt32 height) override;

		private:
			UInt32 _handle = 0;

			UInt32 _width = 0;
			UInt32 _height = 0;
		};
	}
}