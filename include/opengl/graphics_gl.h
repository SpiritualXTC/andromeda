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


namespace andromeda
{

	
	class GraphicsOpenGL : virtual public Graphics
	{
	public:
		static inline void setEnable(GLenum glCap, Boolean enable)
		{
			if (enable)
				glEnable(glCap);
			else
				glDisable(glCap);
		}

		// May move these to another class who's entire purpose is the conversions
		// Conversion Functions
		static inline GLenum convFaceDirection(FaceDirection face)
		{
			static GLenum dat[]
			{
				GL_CW,
				GL_CCW
			};

			return dat[(Int32)face];
		}

		static inline GLenum convCullMode(CullMode cull)
		{
			static GLenum dat[]
			{
				GL_FRONT,
				GL_BACK,
				GL_FRONT_AND_BACK,
				GL_INVALID_ENUM
			};

			return dat[(Int32)cull];
		}

		static inline GLenum convFaceMode(FaceMode face)
		{
			static GLenum dat[]
			{
				GL_FRONT,
				GL_BACK,
				GL_FRONT_AND_BACK
			};

			return dat[(Int32)face];
		}

		static inline GLenum convPolygonMode(PolygonMode polygon)
		{
			static GLenum dat[]
			{
				GL_FILL,
				GL_LINE
			};

			return dat[(Int32)polygon];
		}


		static inline GLenum convFunction(Function func)
		{
			static GLenum dat[]
			{
				GL_NEVER,
				GL_LESS,
				GL_EQUAL,
				GL_LEQUAL,
				GL_GREATER,
				GL_NOTEQUAL,
				GL_GEQUAL,
				GL_ALWAYS
			};

			return dat[(Int32)func];
		}

		static inline GLenum convBlendEquation(BlendEquation equation)
		{
			static GLenum dat[]
			{
				GL_FUNC_ADD,
				GL_FUNC_SUBTRACT,
				GL_FUNC_REVERSE_SUBTRACT,
				GL_MIN,
				GL_MAX
			};

			return dat[(Int32)equation];
		}

		static inline GLenum convBlendFunction(BlendFunction function)
		{
			static GLenum dat[]
			{
				GL_ZERO,
				GL_ONE,

				GL_SRC_COLOR,
				GL_ONE_MINUS_SRC_COLOR,

				GL_DST_COLOR,
				GL_ONE_MINUS_DST_COLOR,

				GL_SRC_ALPHA,
				GL_ONE_MINUS_SRC_ALPHA,

				GL_DST_ALPHA,
				GL_ONE_MINUS_DST_ALPHA,

				GL_CONSTANT_COLOR,
				GL_ONE_MINUS_CONSTANT_COLOR,

				GL_CONSTANT_ALPHA,
				GL_ONE_MINUS_CONSTANT_ALPHA,

				GL_SRC_ALPHA_SATURATE
			};

			return dat[(Int32)function];
		}



		static inline GLenum convStencilOperation(StencilOperation op)
		{
			static GLenum dat[]
			{
				GL_ZERO,
				GL_KEEP,
				GL_REPLACE,
				GL_INCR,
				GL_INCR_WRAP,
				GL_DECR,
				GL_DECR_WRAP,
				GL_INVERT
			};

			return dat[(Int32)op];
		}


		static inline GLenum convDataType(DataType dataType)
		{
			static GLenum dat[]
			{
				GL_BYTE,
				GL_UNSIGNED_BYTE,
				GL_SHORT,
				GL_UNSIGNED_SHORT,
				GL_INT,
				GL_UNSIGNED_INT,
				GL_FLOAT,
				GL_FIXED,
			};

			return dat[(Int32)dataType];
		}


		static inline GLenum convStorageFormatInternal(StorageFormat format)
		{
			static GLenum dat[]
			{
				GL_RGBA,

				GL_RGBA16F,
				GL_RGBA32F,

				GL_DEPTH_COMPONENT16,
				GL_DEPTH_COMPONENT24,
				GL_DEPTH_COMPONENT32,

				GL_DEPTH_STENCIL
			};

			
			return dat[(Int32)format];
		}
		static inline GLenum convStorageFormat(StorageFormat format)
		{
			// Same as above... only the simpler version... lol
			// https://www.opengl.org/sdk/docs/man/html/glTexImage2D.xhtml
			static GLenum dat[]
			{
				GL_RGBA,

				GL_RGBA,
				GL_RGBA,

				GL_DEPTH_COMPONENT,
				GL_DEPTH_COMPONENT,
				GL_DEPTH_COMPONENT,

				GL_DEPTH_STENCIL
			};


			return dat[(Int32)format];
		}



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


		/*
			Creation
		*/
		std::shared_ptr<IFrameBuffer> createFrameBuffer(Int32 width, Int32 height) override;




		/*
			Important Functions
		*/
		inline void setViewport(Int32 x, Int32 y, Int32 width, Int32 height) override
		{
			glViewport(x, y, width, height);
		}


		/*
			Common States
		*/
		inline void setFrontFace(FaceDirection face) override
		{
			glFrontFace(convFaceDirection(face));
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
				glCullFace(convCullMode(cull));
			}
		}

		inline void setPolygonMode(FaceMode face, PolygonMode mode) override
		{
			glPolygonMode(convFaceMode(face), convPolygonMode(mode));
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
			glBlendEquationSeparate(convBlendEquation(rgbEquation), convBlendEquation(alphaEquation));
		}

		inline void setBlendFunction(BlendFunction source, BlendFunction destination)
		{
			setBlendFunction(source, source, destination, destination);
		}
		inline void setBlendFunction(BlendFunction rgbSource, BlendFunction rgbDest
			, BlendFunction alphaSource, BlendFunction alphaDest
			)
		{
			glBlendFuncSeparate(convBlendFunction(rgbSource), convBlendFunction(rgbDest)
				, convBlendFunction(alphaSource), convBlendFunction(alphaDest));
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
			glDepthFunc(convFunction(func));
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
			glStencilFuncSeparate(convFaceMode(face), convFunction(function), ref, mask);
		}

		inline void setStencilMask(UInt32 mask, FaceMode face = FaceMode::FrontAndBack) override
		{
			glStencilMaskSeparate(convFaceMode(face), mask);
		}

		inline void setStencilOperation(StencilOperation stencilFail
			, StencilOperation depthFail
			, StencilOperation depthPass
			, FaceMode face = FaceMode::FrontAndBack
			) override
		{
			glStencilOpSeparate(convFaceMode(face), convStencilOperation(stencilFail)
				, convStencilOperation(depthFail), convStencilOperation(depthPass));
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

