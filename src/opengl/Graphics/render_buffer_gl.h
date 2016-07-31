#pragma once

#include <andromeda/Graphics/frame_buffer.h>


#include <andromeda/graphics_types.h>

namespace andromeda
{
	namespace opengl
	{
		/*
		
		*/
		class RenderBufferGL : public ITexture2D
		{
		public:
			RenderBufferGL(Int32 width, Int32 height, UInt32 attachment, StorageFormat format = StorageFormat::RGBA, DataType dataType = DataType::UnsignedByte);
			virtual ~RenderBufferGL();

			const Int32 width() const override { return _width; }
			const Int32 height() const override { return _height; }


			// Binds the RenderBuffer
			void bindBuffer();	// Don't think these are even needed

			// Unbinds the RenderBuffer
			void unbindBuffer();// Don't think these are even needed




			// Binds the RenderBuffer as a texture
			void bind();

			// Unbinds the RenderBuffer as a texture
			void unbind();


			void setSize(Int32 width, Int32 height);


		private:
			Int32 _width = 0;
			Int32 _height = 0;

			DataType _dataType = DataType::UnsignedByte;
			StorageFormat _format = StorageFormat::RGBA;
			UInt32 _attachment = 0;


			UInt32 _buffer = 0;
			UInt32 _texture = 0;

			
		};

	}
}