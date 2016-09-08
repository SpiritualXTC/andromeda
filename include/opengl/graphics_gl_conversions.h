#pragma once

#include <andromeda/stddef.h>
#include <andromeda/graphics_types.h>

/*
	TODO:
	This include should be local only to the OpenGL project
*/
#include <andromeda/opengl.h>

namespace andromeda
{
	namespace opengl
	{


		// May move these to another class who's entire purpose is the conversions
		// Conversion Functions
		inline GLenum convFaceDirection(FaceDirection face)
		{
			static GLenum dat[]
			{
				GL_CW,
				GL_CCW
			};

			return dat[(Int32)face];
		}

		inline GLenum convCullMode(CullMode cull)
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

		inline GLenum convFaceMode(FaceMode face)
		{
			static GLenum dat[]
			{
				GL_FRONT,
				GL_BACK,
				GL_FRONT_AND_BACK
			};

			return dat[(Int32)face];
		}

		inline GLenum convPolygonMode(PolygonMode polygon)
		{
			static GLenum dat[]
			{
				GL_FILL,
				GL_LINE
			};

			return dat[(Int32)polygon];
		}


		inline GLenum convFunction(Function func)
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

		inline GLenum convBlendEquation(BlendEquation equation)
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

		inline GLenum convBlendFunction(BlendFunction function)
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



		inline GLenum convStencilOperation(StencilOperation op)
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


		inline GLenum convDataType(DataType dataType)
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


		inline GLenum convStorageFormatInternal(StorageFormat format)
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


		inline GLenum convStorageFormat(StorageFormat format)
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


		inline GLint convTextureMagFilter(TextureMagFilter filter)
		{
			static GLenum dat[]
			{
				GL_NEAREST,
				GL_LINEAR,
			};

			return dat[(Int32)filter];
		}

		inline GLint convTextureMinFilter(TextureMinFilter filter)
		{
			static GLenum dat[]
			{
				GL_NEAREST,
				GL_LINEAR,

				GL_NEAREST_MIPMAP_NEAREST,
				GL_LINEAR_MIPMAP_NEAREST,

				GL_NEAREST_MIPMAP_LINEAR,
				GL_LINEAR_MIPMAP_LINEAR,
			};

			return dat[(Int32)filter];
		}	

		inline GLenum convTextureWrapMode(TextureWrapMode wrapMode)
		{
			static GLenum dat[]
			{
				GL_REPEAT,
				GL_MIRRORED_REPEAT,
				GL_CLAMP_TO_EDGE,
			};

			return dat[(Int32)wrapMode];
		}
	}
}