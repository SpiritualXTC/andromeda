#pragma once

#include <GL/glew.h>

#include <core/Graphics/texture.h>

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
			TextureGL(UInt32 width, UInt32 height, StorageFormat storageFormat = StorageFormat::RGBA);
			virtual ~TextureGL();


			const inline UInt32 width() const override { return _width; }
			const inline UInt32 height() const override { return _height; }
			const inline StorageFormat format() const override { return _format; }



			void bind(UInt32 activeIndex) const override;
			void unbind(UInt32 activeIndex) const override;



			//void resize(const UInt8 * ptr, UInt32 width, UInt32 height) override;
			void resize(UInt32 width, UInt32 height, StorageFormat storageFormat, const UInt8 * ptr) override;


			void data(const UInt8 * ptr) override;
			void data(const UInt8 * ptr, Int32 xOffset, Int32 yOffset, UInt32 width, UInt32 height) override;



			void filter(TextureMagFilter magFilter, TextureMinFilter minFilter) override;
			void wrap(TextureWrapMode wrapMode) override;


		private:
			UInt32 _handle = 0;	// TODO: Gluint?

			UInt32 _width = 0;
			UInt32 _height = 0;

			TextureMagFilter _magFilter = TextureMagFilter::Linear;
			TextureMinFilter _minFilter = TextureMinFilter::Linear;

			TextureWrapMode _wrap = TextureWrapMode::Repeat;

			StorageFormat _format = StorageFormat::RGBA;
		};
	}
}