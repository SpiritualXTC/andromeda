#ifndef _ANDROMEDA_GRAPHICS_RENDER_TARGET_H_
#define _ANDROMEDA_GRAPHICS_RENDER_TARGET_H_

#include <memory>
#include <vector>

#include <andromeda/stddef.h>

#include "texture.h"
#include <andromeda/opengl.h>

namespace andromeda
{

	/*
	
	*/
	class IRenderTarget //: public ITexture
	{
	public:
		IRenderTarget() {}
		virtual ~IRenderTarget() {}

		virtual const Int32 width() const = 0;
		virtual const Int32 height() const = 0;

		virtual void clear() = 0;
		virtual void bindFrame() = 0;
		virtual void unbindFrame() = 0;
	};




	/*
		RenderTargets can be made up of 1 or more textures.

		However the lazy version just extends texture!
	*/
	class RenderTarget : public Texture, public IRenderTarget
	{
	public:
		RenderTarget(Int32 width, Int32 height);
		virtual ~RenderTarget();

		void clear() override;

		void bindFrame() override;
		void unbindFrame() override;

		const inline Int32 width() const override { return Texture::width(); }
		const inline Int32 height() const override { return Texture::height(); }

	private:
		GLuint _frameBuffer = 0;
	};


	/*
	
	*/
	class RenderTarget2 : virtual public IRenderTarget, virtual public ITexture
	{
	public:
		RenderTarget2(Int32 width, Int32 height, Int32 buffers = 2);
		virtual ~RenderTarget2();



		void clear() override;

		void bindFrame() override;		/* Changes the buffer*/
		void unbindFrame() override;

		const inline Int32 width() const override { return _width; }
		const inline Int32 height() const override { return _height; }

		void bind() override;
		void unbind() override;

	private:
		Int32 _width = 0;
		Int32 _height = 0;


		GLuint * _textures = nullptr;
		GLuint * _buffers = nullptr;
		UInt32 _bufferCount = 0;

		GLuint _texture = -1;	// Current Texture Handle
		GLuint _buffer = -1;	// Current Frame buffer
		UInt32 _index = 0;		// Current Index
	};
}


#endif