#pragma once

#include <andromeda/Graphics/frame_buffer.h>

#include "render_buffer_gl.h"

namespace andromeda
{
	namespace opengl
	{

		class FrameBufferGL : public IFrameBuffer
		{
		private:

		public:
			FrameBufferGL(Int32 width, Int32 height);
			virtual ~FrameBufferGL();

			const Int32 width() const { return _width; }
			const Int32 height() const { return _height; }

			// Get the Texture
			std::shared_ptr<ITexture> getTexture(UInt32 index) override { return _buffers[index]; }
			//const std::shared_ptr<ITexture> getTexture(UInt32 index) const { return _buffers[index]; }


			// Get Number of buffers in use
			const UInt32 getBufferCount() const { return _buffers.size(); }



			/*
				Binds the Framebuffer
			*/
			void bind() override;

			/*
				Unbinds the Framebuffer
			*/
			void unbind() override;


			// Resize the FrameBuffer
			void resize(Int32 width, Int32 height) override;



			Boolean status();

		protected:
			void attach(UInt32 attachment, StorageFormat format, DataType dataType);

		private:
			Int32 _width = 0;
			Int32 _height = 0;


			UInt32 _frameBuffer = 0;


			std::shared_ptr<RenderBufferGL> _depth;	// Depth Buffer

			std::vector<UInt32> _attachments;
			std::vector<std::shared_ptr<RenderBufferGL>> _buffers; 
		};

	}
}