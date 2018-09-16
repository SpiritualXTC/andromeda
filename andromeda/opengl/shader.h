#pragma once

#include <string>
#include <memory>

#include <common/exception.h>
#include <core/Graphics/shader.h>

#include <GL/glew.h>

namespace andromeda
{
	namespace opengl
	{
		enum ShaderType
		{
			VertexShader,
			FragmentShader,

			GeometryShader,
		};

		class ShaderException : virtual public Exception 
		{
		public:
			ShaderException(const std::string& msg) : Exception(msg) {}
		};

		class ShaderGL
		{
		public:
			static const GLuint SHADER_INVALID_HANDLE = 0xFFFFFFFF;
			static GLenum GetShaderType(ShaderType shaderType);		// TODO: this can be moved to the central graphics routines

		public:
			ShaderGL(ShaderType type);
			virtual ~ShaderGL();

			/* Checks whether their is a valid handle */
			inline Boolean isValid() const { return _handle != SHADER_INVALID_HANDLE; }

			/* Compiles a Shader */
			GLuint compile(const std::string & source);

			/* Release Shader */
			void release();

			const inline GLuint handle() { return _handle; }

		private:
			ShaderType _shaderType;
			GLuint _handle = SHADER_INVALID_HANDLE;
		};



	}
}