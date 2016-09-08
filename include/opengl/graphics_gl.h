#pragma once

#include <andromeda/graphics.h>


/*
	TODO:
	Add a OpenGL header [HERE] that selects the apprioriate OpenGL header[s] by platform

	This can only be done when:
	 - The XEffect Engine is in place
	 - OpenGL includes is NOT part of graphics.h
	 - All openGL functions in the Engine have been replaced with API agnostic functions from the Graphics API


	Don't think this header file should be here...
*/


/*
	TODO:
	This should NOT extend graphics ... in fact there shouldn't even be a header file.

	The SOURCE file should be implementation specific -- but only using the andromeda::Graphics class
	as there should only be one implementation /link

	However this may make supporting numerous versions of OpenGL rather confusing :P (Except for Vulkan, as that would be 100% separate)

	This can ONLY be done after the Core Library has been divided into sub-libraries
*/
#include "graphics_gl_conversions.h"


namespace andromeda
{

	
	class GraphicsOpenGL : virtual public Graphics
	{
	public:
		GraphicsOpenGL() 
		{
			/*
				TODO:
				Enable this option in the effect engine
			*/
			//glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
		}
		virtual ~GraphicsOpenGL() {}



		// Change Internal State
		inline void setEnable(GLenum glCap, Boolean enable)
		{
			if (enable)
				glEnable(glCap);
			else
				glDisable(glCap);
		}



		/*
			Creation
		*/
		std::shared_ptr<IFrameBuffer> createFrameBuffer(UInt32 width, UInt32 height) override;

		// Create Texture
		std::shared_ptr<Texture> createTexture(UInt32 width, UInt32 height, StorageFormat format) override;

		// Create Cube Texture
		std::shared_ptr<CubeTexture> createCubeTexture(UInt32 width, UInt32 height) override;

		// Create Volume Texture [No Implementation]
		std::shared_ptr<VolumeTexture> createVolumeTexture() override;

		// Create Shader
		std::shared_ptr<IShader> createShader() override;

		// Create Buffers
		std::shared_ptr<VertexBuffer> createVertexBuffer() override;

		std::shared_ptr<IndexBuffer> createIndexBuffer() override;



		/*
			Important Functions
		*/






		// Important States
		inline void setClearColor(Float r, Float g, Float b, Float a) override
		{
			glClearColor(r, g, b, a);
		}


		inline void setViewport(Int32 x, Int32 y, Int32 width, Int32 height) override
		{
			glViewport(x, y, width, height);
		}


		/*
			Common States
		*/
		inline void setFrontFace(FaceDirection face) override
		{
			glFrontFace(opengl::convFaceDirection(face));
		}
		inline void setCulling(CullMode cull) override
		{
			// Disables Culling
			// Or
			// Enables Culling and Sets whats face to cull

			if (cull == CullMode::None)
				glDisable(GL_CULL_FACE);
			else
			{
				glEnable(GL_CULL_FACE);
				glCullFace(opengl::convCullMode(cull));
			}
		}

		inline void setPolygonMode(FaceMode face, PolygonMode mode) override
		{
			glPolygonMode(opengl::convFaceMode(face), opengl::convPolygonMode(mode));
		}


		/*
			Blend Functions
		*/
		inline void setBlendEnabled(Boolean enable) override
		{
			setEnable(GL_BLEND, enable);
		}
		inline void setBlendColor(Float r, Float g, Float b, Float a)
		{
			glBlendColor(r, g, b, a);
		}
		inline void setBlendEquation(BlendEquation equation)
		{
			setBlendEquation(equation, equation);
		}
		inline void setBlendEquation(BlendEquation rgbEquation, BlendEquation alphaEquation)
		{
			glBlendEquationSeparate(opengl::convBlendEquation(rgbEquation), opengl::convBlendEquation(alphaEquation));
		}

		inline void setBlendFunction(BlendFunction source, BlendFunction destination)
		{
			setBlendFunction(source, source, destination, destination);
		}
		inline void setBlendFunction(BlendFunction rgbSource, BlendFunction rgbDest
			, BlendFunction alphaSource, BlendFunction alphaDest
			)
		{
			glBlendFuncSeparate(opengl::convBlendFunction(rgbSource), opengl::convBlendFunction(rgbDest)
				, opengl::convBlendFunction(alphaSource), opengl::convBlendFunction(alphaDest));
		}


		/* 
			Depth Functions 
		*/
		inline void setDepthEnable(Boolean enable) override
		{
			setEnable(GL_DEPTH_TEST, enable);
		}
		inline void setDepthFunction(Function func) override
		{
			glDepthFunc(opengl::convFunction(func));
		}
		inline void setDepthWriteEnable(Boolean enable) override
		{
			glDepthMask(enable);
		}
		inline void setDepthRange(Float zNear, Float zFar) override
		{
			glDepthRange(zNear, zFar);
		}



		/*
			Stencil Functions
		*/
		inline void setStencilEnable(Boolean enable) override
		{
			setEnable(GL_STENCIL_TEST, enable);
		}

		inline void setStencilFunction(Function function, Int32 ref, UInt32 mask, FaceMode face = FaceMode::FrontAndBack) override
		{
			glStencilFuncSeparate(opengl::convFaceMode(face), opengl::convFunction(function), ref, mask);
		}

		inline void setStencilMask(UInt32 mask, FaceMode face = FaceMode::FrontAndBack) override
		{
			glStencilMaskSeparate(opengl::convFaceMode(face), mask);
		}

		inline void setStencilOperation(StencilOperation stencilFail
			, StencilOperation depthFail
			, StencilOperation depthPass
			, FaceMode face = FaceMode::FrontAndBack
			) override
		{
			glStencilOpSeparate(opengl::convFaceMode(face), opengl::convStencilOperation(stencilFail)
				, opengl::convStencilOperation(depthFail), opengl::convStencilOperation(depthPass));
		}


		/*
			Drawing
		*/
		void clear() override
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		}


		/*
			Behavior
		*/
		Int32 getLastError() override;
		void errorCheck() override;


	private:


	};
}

