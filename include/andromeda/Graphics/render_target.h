#ifndef _ANDROMEDA_GRAPHICS_RENDER_TARGET_H_
#define _ANDROMEDA_GRAPHICS_RENDER_TARGET_H_

#include <memory>
#include <vector>

#include "../stddef.h"

#include "texture.h"
#include "opengl.h"

namespace andromeda
{

	/*
	
	*/
	class IRenderTarget : public ITexture
	{
	public:
		IRenderTarget() {}
		virtual ~IRenderTarget() {}

		virtual void clear() = 0;
		virtual void bindFrame() = 0;
		virtual void unbindFrame() = 0;
	};



	/*
		RenderTargets can be made up of 1 or more textures.

		However the lazy version just extends texture!
	*/
	class RenderTarget : public Texture//, public IRenderTarget
	{
	public:
		RenderTarget(Int32 width, Int32 height);
		virtual ~RenderTarget();

		void clear();// override;

		void bindFrame();// override;
		void unbindFrame();// override;

	private:
		GLuint _frameBuffer = 0;
	};


	/*
	
	*/
	class RenderTarget2 : public IRenderTarget
	{
	public:
		RenderTarget2(Int32 width, Int32 height, Int32 buffers = 2);
		virtual ~RenderTarget2();



		void clear() override;

		void bindFrame() override;		/* Changes the buffer*/
		void unbindFrame() override;

		void bind() override;
		void unbind() override;

	private:
		std::vector<GLuint> _textures;
		GLuint _framebuffers = 0;
	};

}


#endif