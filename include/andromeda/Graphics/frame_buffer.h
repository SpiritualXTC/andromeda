#pragma once

#include <vector>

#include "texture.h"


namespace andromeda
{
#if 0
	/*
		Interface for RenderBuffers... this may not need to be exposed...
	*/
	class IRenderBuffer : ITexture2D
	{
	public:
		// Binds the RenderBuffer
		virtual void bindBuffer() = 0;

		// Unbinds the RenderBuffer
		virtual void unbindBuffer() = 0;

	};
#endif



	/*
		Interface for the FrameBuffer
	*/
	class IFrameBuffer
	{
	public:
		virtual const Int32 width() const = 0;
		virtual const Int32 height() const = 0;

		/*
			Binds the Framebuffer
		*/
		virtual void bind() = 0;

		/*
			Unbinds the Framebuffer
		*/
		virtual void unbind() = 0;

		// Resize the FrameBuffer
		virtual void resize(Int32 width, Int32 height) = 0;



		virtual const UInt32 getBufferCount() const = 0;

		/*
			Gets the Texture @ index
		*/
		virtual std::shared_ptr<ITexture> getTexture(UInt32 index) = 0;
	};









}
